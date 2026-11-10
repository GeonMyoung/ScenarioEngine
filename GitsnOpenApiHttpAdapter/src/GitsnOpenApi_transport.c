#include "GitsnOpenApiArg.h"
#include "GitsnOpenApi_servant.h"
#include "../../dimz/dz1/src/socket/dz1_socket_callback_skel.h"

/* The vendored callback socket deliberately hides getOSHandle after association.
 * Keep its descriptor protected by the same lock as close, rather than caching
 * a descriptor that may be closed and reused by another connection. This bridge
 * is private to the Agent's statically linked HTTP transport. */
bool_t GitsnOpenApi_shutdownSend(Dz1TcpClientSocket *socket, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    Dz1SocketCallback2Spec *spec;
    int result;
    if (socket == NULL || socket->specific == NULL ||
        socket->specific_del != (Dz1DelFunc)Dz1SocketCallback2Spec_del)
    { ERR_SET_OUT(errp, EINVAL); return FALSE; }
    spec = (Dz1SocketCallback2Spec *)socket->specific;
    pthread_mutex_lock(&spec->lock);
    if (spec->own_sock.specific == NULL || spec->own_sock.specific_del == NULL)
        Dz1Error_set(errp, EPIPE);
    else
    {
#ifndef UNIX_SYSTEM
        result = shutdown(spec->fd, SD_SEND);
        Dz1Error_set(errp, result == 0 ? 0 : WSAGetLastError());
#else
        result = shutdown(spec->fd, SHUT_WR);
        Dz1Error_set(errp, result == 0 ? 0 : errno);
#endif
    }
    pthread_mutex_unlock(&spec->lock);
    return ERR_IS_SUCCESS(errp);
}
