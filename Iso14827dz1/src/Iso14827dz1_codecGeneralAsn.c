#ifdef GITSN_GENERAL_ASN_TOOL
#include "Iso3309CRC.h"
#include "Iso14827dz1_codec.h"
#include "Iso14827dz1_conv.h"

ssize_t Iso14827C2CAuthMsg_decodeBer(Iso14827C2CAuthMsg **retMsg, u8_t *buf, size_t size, Dz1Error *errp)
{
	DatexDataPacket_t *packet = NULL;
	ssize_t ret = asn1msg_dec(&asn_DEF_DatexDataPacket, (void **)&packet, buf, size, errp);
	if (ret < 0) ERR_OUT(errp);
	else if (ret == 0) return 0;
	else
	{
		pthread_cleanup_push((Dz1DelFunc)DatexDataPacket_del, (void *)packet);
		
		if (packet->datex_Version_number != datex_Version_number_version1) { ret = -1; ERR_SET_OUT(errp, EINVAL); }
		else
		{
			uint16_t packet_crc =  ((uint16_t)packet->datex_Crc_nbr.buf[0]) << 8 | (uint16_t)packet->datex_Crc_nbr.buf[1];
			uint16_t crc = Iso3309Crc(packet->datex_Data.buf, packet->datex_Data.size);
			if (crc != packet_crc)
			{
				Dz1Thread_printf("CEC mismatch %02X : %04X\n", packet_crc, crc);
				ERR_SET_OUT(errp, EINVAL);
				ret = -1;
			}
			else
			{
				C2CAuthenticatedMessage_t *msg = NULL;
				ssize_t temp = asn1msg_dec(&asn_DEF_C2CAuthenticatedMessage, (void **)&msg, packet->datex_Data.buf, packet->datex_Data.size, errp);
				if (temp < 0) { ERR_OUT(errp); ret = -1; }
				else
				{	// Post Message to parent task
					pthread_cleanup_push((Dz1DelFunc)C2CAuthenticatedMessage_del, (void *)msg);
					
					Dz1Thread_printf("Iso14827C2CAuthMsg_decodeBer :: Decodded = ");
					C2CAuthenticatedMessage_dump(msg, 1);
					
					if ((*errp = Iso14827C2CAuthMsg_fromASN(retMsg, msg)).code) { ret = -1; ERR_OUT(errp); }
					
					pthread_cleanup_pop(1); // ((Dz1DelFunc)C2CAuthenticatedMessage_del, (void *)msg);
				}
			}
		}
		
		pthread_cleanup_pop(1); // ((Dz1DelFunc)DatexDataPacket_del, (void *)packet);
	}

	return ret;
}

static int _dummy(const void *buffer, size_t size, void *app_key) { return 0; }
ssize_t Iso14827C2CAuthMsg_encodeBer(C2CAuthenticatedMessage_t *src, u8_t **dst, Dz1Error *errp)
{
	ssize_t ret = -1;
	DatexDataPacket_t *pkt = (DatexDataPacket_t *)calloc(sizeof(DatexDataPacket_t), 1);
	if (pkt == NULL) ERR_SET_OUT(errp, ENOMEM);
	else
	{
		u8_t *temp = NULL;
		ssize_t tmpSize = -1;
		pthread_cleanup_push((Dz1DelFunc)DatexDataPacket_del, (void *)pkt);
		if ((tmpSize = asn1msg_enc(&asn_DEF_C2CAuthenticatedMessage, (void *)src, &temp, errp)) < 0) ERR_OUT(errp);
		else
		{
			u16_t crc = 0;
			char _crc[2];
			pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);

			crc = Iso3309Crc(temp, tmpSize);
			_crc[0] = (u8_t)((crc >> 8) & 0x00FF);
			_crc[1] = (u8_t)(crc & 0x00FF);

			pkt->datex_Version_number = datex_Version_number_version1;
			if (OCTET_STRING_fromBuf(&pkt->datex_Data, temp, tmpSize) < 0) ERR_SET_OUT(errp, EFAULT);
			else if (OCTET_STRING_fromBuf(&pkt->datex_Crc_nbr, _crc, 2) < 0) ERR_SET_OUT(errp, EFAULT);
			else if ((ret = asn1msg_enc(&asn_DEF_DatexDataPacket, (void *)pkt, dst, errp)) < 0) ERR_OUT(errp);
			else
			{
				Dz1Thread_printf("Iso14827C2CAuthMsg_encodeBer(%d) = ", ret); DatexDataPacket_dump(pkt, 1);
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)DatexDataPacket_del, (void *)pkt);
	}
	return ret;
}

ssize_t Dz1Asn1OctetStr_decodeBer(Dz1Asn1OctetStr **dst, u8_t *src, size_t size, Dz1Error *errp)
{
	ssize_t _ret = -1;
	OCTET_STRING_t *temp = NULL;
	if ((_ret = asn1msg_dec(&asn_DEF_OCTET_STRING, (void **)&temp, src, size, errp)) < 0) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push((Dz1DelFunc)OCTET_STRING_del, (void *)temp);

		if ((*dst = Dz1Asn1OctetStr_new(temp->buf, temp->size, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // ((Dz1DelFunc)OCTET_STRING_del, (void *)temp);
	}
	return _ret;
}

ssize_t Dz1Asn1OctetStr_encodeBer(u8_t **dst, Dz1Asn1OctetStr *src, Dz1Error *errp)
{
	ssize_t _ret = -1;
	OCTET_STRING_t *temp = NULL;
	if ((temp = OCTET_STRING_new_fromBuf(&asn_DEF_OCTET_STRING, src->data, src->size)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push((Dz1DelFunc)OCTET_STRING_del, (void *)temp);
		if ((_ret = asn1msg_enc(&asn_DEF_OCTET_STRING, (void *)temp, dst, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // ((Dz1DelFunc)OCTET_STRING_del, (void *)temp);
	}
	return _ret;
}

#endif