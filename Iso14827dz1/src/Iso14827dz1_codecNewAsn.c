#if defined(GITSN_NEW_ASN_TOOL)

#include <dz1_int.h>
#include <dz1_thread_stdio.h>

#include <ISO14827_1.h>
#include <ISO14827_2.h>

#include <Iso14827dz1_assist.h>

#include "Iso3309CRC.h"

#include "Iso14827dz1_conv.h"

#ifdef __BORLANDC__
#pragma warn -8004
#endif
///////////////////////////////////////////////////////////////////////////////
// Iso14827C2CAuthMsg BER CODEC
///////////////////////////////////////////////////////////////////////////////
static ssize_t Iso14827C2CAuthMsg_decodeBerDatex(Iso14827C2CAuthMsg **retMsg, u8_t *buf, size_t size, Dz1Error *errp)
{
	ssize_t ret = -1;
 	
	if ( buf == NULL ) ERR_SET_OUT(errp, EINVAL);
	else 
	{
		ssize_t status = 0;
		DatexDataPacket packet;
		ASN1WorkSpace pktWS;
		//int len =0;
		ASN1_INIT_WS_INFO(&pktWS);
		pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&pktWS);

		ASN1_Save_WORKSPACE(&pktWS, buf, size);
		pktWS.dataSize = size;

		if (( status = ASN1_BER_Dec_DatexDataPacket(&pktWS, &packet, size, ASN1EXPL)) < 0) { ret = status; ERR_SET_OUT(errp, EFAULT); }
		else  
		{
			ret = pktWS.buffer.current - pktWS.buffer.data;

			if (packet.datex_Version_number > DatexDataPacket_datex_Version_number_version1) { ret = -1; ERR_SET_OUT(errp, EINVAL); }
			else
 			{
 				uint16_t packet_crc =  ((uint16_t)packet.datex_Crc_nbr.data[0]) << 8 | (uint16_t)packet.datex_Crc_nbr.data[1];
 				uint16_t crc = Iso3309Crc(packet.datex_Data.data, packet.datex_Data.numbits);
 				if (crc != packet_crc) { ERR_SET_OUT(errp, EINVAL);	ret = -1;}
 				else
 				{
 					
					C2CAuthenticatedMessage msg;
					
 					ASN1WorkSpace localWS;
 					ASN1_INIT_WS_INFO(&localWS);
					pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&localWS);

					ASN1_Save_WORKSPACE(&localWS, packet.datex_Data.data, packet.datex_Data.numbits);
					localWS.dataSize = packet.datex_Data.numbits;

 					if (( status = ASN1_BER_Dec_C2CAuthenticatedMessage(&localWS, &msg, packet.datex_Data.numbits, ASN1EXPL)) < 0) { ret = status; ERR_SET_OUT(errp, EFAULT); }
 					else 
 					{	
						//Dz1Thread_printf("Iso14827C2CAuthMsg_decodeBer() : Decoded = ");
						//ASN1_Print_C2CAuthenticatedMessage(&msg, 1);

 						if ((*errp = Iso14827C2CAuthMsg_fromASN(retMsg, &msg)).code) ERR_SET_OUT(errp, EFAULT);
 						
 					}
					pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&localWS);
 				}
			}
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&pktWS);
	}	
	
	return ret;
}

static ssize_t Iso14827C2CAuthMsg_encodeBerDatex(C2CAuthenticatedMessage *src, u8_t **dst, ASN1WorkSpace *ws, Dz1Error *errp)
{
	ssize_t ret = -1, status = 0;

	//Dz1Thread_printf("Iso14827C2CAuthMsg_encodeBer() : Source = ");
	//ASN1_Print_C2CAuthenticatedMessage(src, 1);

	if ((status = ASN1_BER_Enc_C2CAuthenticatedMessage(ws, src, ASN1EXPL)) < 0) { ret = status; ERR_SET_OUT(errp, EFAULT); }
	else if ((status = IndefinelenTodefinelen(ws)) < 0) { ret = status; ERR_SET_OUT(errp, EFAULT); }
	else
	{
		DatexDataPacket packet;

		uint16_t crc = 0;
		u8_t _crc[2];
		
		ASN1WorkSpace pktWS;
		ASN1_INIT_WS_INFO(&pktWS);
		pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&pktWS);
		
		// Setup DatexDataPacket
		// Dz1Thread_printb(ws->buffer.data, GetDataLength(ws), 16);
		crc = Iso3309Crc(ws->buffer.data, GetDataLength(ws));
		_crc[0] = (u8_t)((crc >> 8) & 0x00FF);
		_crc[1] = (u8_t)(crc & 0x00FF);

		packet.datex_Version_number = DatexDataPacket_datex_Version_number_version1;
		if ((status = ASN1_SET_DatexDataPacket_datex_Data(&pktWS, &packet, ws->buffer.data, GetDataLength(ws))) < 0) { ret = status; ERR_SET_OUT(errp, EFAULT); }
		else if ((status = ASN1_SET_DatexDataPacket_datex_Crc_nbr(&pktWS, &packet, _crc, 2)) < 0) { ret = status; ERR_SET_OUT(errp, EFAULT); }
		else
		{
			// Encode Packet
			if ((status = ASN1_BER_Enc_DatexDataPacket(&pktWS, &packet, ASN1EXPL)) < 0) { ret = status; ERR_SET_OUT(errp, EFAULT); }
			else if ((status = IndefinelenTodefinelen(&pktWS)) < 0) { ret = status; ERR_SET_OUT(errp, EFAULT); }
			else if ((*dst = (u8_t *)Dz1Malloc((ret = GetDataLength(&pktWS)), errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				// ASN1_Print_DatexDataPacket(&packet, 0);
				memcpy((*dst), pktWS.buffer.data, ret);
			}
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&pktWS);
	}

	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Iso14827C2CAuthMsg Unaligned PER CODEC
///////////////////////////////////////////////////////////////////////////////
static ssize_t Iso14827C2CAuthMsg_decodeUperDatex(Iso14827C2CAuthMsg **retMsg, u8_t *buf, size_t size, Dz1Error *errp)
{
	ssize_t ret = -1;
	
	if ( buf == NULL ) ERR_SET_OUT(errp, EINVAL);
	else 
	{
		ssize_t status = 0;
		DatexDataPacket packet;
		ASN1WorkSpace pktWS;
		//int len =0;
		ASN1_INIT_WS_INFO(&pktWS);
		pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&pktWS);
		
		ASN1_Save_WORKSPACE(&pktWS, buf, size);
		pktWS.dataSize = size;
		
		if (( status = ASN1_PER_UNAlign_Dec_DatexDataPacket(&pktWS, &packet)) < 0) { ret = status; ERR_SET_OUT(errp, EFAULT); }
		else  
		{
			ret = pktWS.buffer.current - pktWS.buffer.data + (pktWS.buffer.bitOffset != 8 ? 1 : 0);
			
			if (packet.datex_Version_number > DatexDataPacket_datex_Version_number_version1) { ret = -1; ERR_SET_OUT(errp, EINVAL); }
			else
			{
				uint16_t packet_crc =  ((uint16_t)packet.datex_Crc_nbr.data[0]) << 8 | (uint16_t)packet.datex_Crc_nbr.data[1];
				uint16_t crc = Iso3309Crc(packet.datex_Data.data, packet.datex_Data.numbits);


				if (crc != packet_crc) Dz1Thread_printf("Iso14827C2CAuthMsg_decodeUper() : Warning!! Invalid CRC(%04X:%04X)\n",
														crc, packet_crc);
// 				{
// 					ret = -1;
// 					//Dz1Thread_printf("Iso14827C2CAuthMsg_decodeUper() : CRC(Size = %u) = PacketCRC:%04X != Calculated CRC:%04X\n",
// 					//	packet.datex_Data.numbits, packet_crc, crc);
// 					ERR_SET_OUT(errp, EINVAL);
// 				}
// 				else
				{
					
					C2CAuthenticatedMessage msg;
					
					ASN1WorkSpace localWS;
					ASN1_INIT_WS_INFO(&localWS);
					pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&localWS);
					
					ASN1_Save_WORKSPACE(&localWS, packet.datex_Data.data, packet.datex_Data.numbits);
					localWS.dataSize = packet.datex_Data.numbits;
					
					if (( ASN1_PER_UNAlign_Dec_C2CAuthenticatedMessage(&localWS, &msg)) < 0) {ERR_SET_OUT(errp, EFAULT);}
					else 
					{	
//						Dz1Thread_printf("Iso14827C2CAuthMsg_decodeUper() : Decoded = ");
//						ASN1_Print_C2CAuthenticatedMessage(&msg, 1);
						
						if ((*errp = Iso14827C2CAuthMsg_fromASN(retMsg, &msg)).code) ERR_SET_OUT(errp, EFAULT);
						
					}
					pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&localWS);
				}
			}
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&pktWS);
	}	
	
	return ret;
}

static ssize_t Iso14827C2CAuthMsg_encodeUperDatex(C2CAuthenticatedMessage *src, u8_t **dst, ASN1WorkSpace *ws, Dz1Error *errp)
{
	ssize_t ret = -1;
	
//	Dz1Thread_printf("Iso14827C2CAuthMsg_encodeUper() : Source = ");
//	ASN1_Print_C2CAuthenticatedMessage(src, 1);

	if ((ASN1_PER_UNAlign_Enc_C2CAuthenticatedMessage(ws, src)) < 0) { ERR_SET_OUT(errp, EFAULT); }
	else
	{
		DatexDataPacket packet;
		
		uint16_t crc = 0;
		u8_t _crc[2];
		size_t size = ws->buffer.current - ws->buffer.data + (ws->buffer.bitOffset != 8 ? 1 : 0);
		
		ASN1WorkSpace pktWS;
		ASN1_INIT_WS_INFO(&pktWS);
		pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&pktWS);

		crc = Iso3309Crc(ws->buffer.data, size);
		_crc[0] = (u8_t)((crc >> 8) & 0x00FF);
		_crc[1] = (u8_t)(crc & 0x00FF);
		
		//Dz1Thread_printf("Iso14827C2CAuthMsg_encodeUper() : CRC(Size = %u) = %02X%02X\n", size, _crc[0], _crc[1]);

		packet.datex_Version_number = DatexDataPacket_datex_Version_number_version1;
		if ((ASN1_SET_DatexDataPacket_datex_Data(&pktWS, &packet, ws->buffer.data, size)) < 0) ERR_SET_OUT(errp, EFAULT);
		else if ((ASN1_SET_DatexDataPacket_datex_Crc_nbr(&pktWS, &packet, _crc, 2)) < 0) ERR_SET_OUT(errp, EFAULT);
		else
		{
			// Encode Packet
			if ((ASN1_PER_UNAlign_Enc_DatexDataPacket(&pktWS, &packet)) < 0) ERR_SET_OUT(errp, EFAULT);
			else
			{
				size_t sz = pktWS.buffer.current - pktWS.buffer.data + (pktWS.buffer.bitOffset != 8 ? 1 : 0);
				if ((*dst = (u8_t *)Dz1Malloc((ret = sz), errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else
				{
					// ASN1_Print_DatexDataPacket(&packet, 0);
					memcpy((*dst), pktWS.buffer.data, ret);
				}
			}
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&pktWS);
	}

	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Iso14827C2CAuthMsg Aligned PER CODEC
///////////////////////////////////////////////////////////////////////////////
static ssize_t Iso14827C2CAuthMsg_decodeAperDatex(Iso14827C2CAuthMsg **retMsg, u8_t *buf, size_t size, Dz1Error *errp)
{
	ssize_t ret = -1;
	
	if ( buf == NULL ) ERR_SET_OUT(errp, EINVAL);
	else 
	{
		DatexDataPacket packet;
		ASN1WorkSpace pktWS;
		//int len =0;
		ASN1_INIT_WS_INFO(&pktWS);
		pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&pktWS);
		
		ASN1_Save_WORKSPACE(&pktWS, buf, size);
		pktWS.dataSize = size;
		
		if (( ASN1_PER_Align_Dec_DatexDataPacket(&pktWS, &packet)) < 0) {ERR_SET_OUT(errp, EFAULT);}
		else  
		{
			ret = pktWS.buffer.current - pktWS.buffer.data + (pktWS.buffer.bitOffset != 8 ? 1 : 0);
			
			//Dz1Thread_printf("Iso14827C2CAuthMsg_decodeAper() : Data Packet = ");
			//ASN1_Print_DatexDataPacket(&packet, 0);

			if (packet.datex_Version_number != DatexDataPacket_datex_Version_number_version1) { ret = -1; ERR_SET_OUT(errp, EINVAL); }
			else
			{
				uint16_t packet_crc =  ((uint16_t)packet.datex_Crc_nbr.data[0]) << 8 | (uint16_t)packet.datex_Crc_nbr.data[1];
				uint16_t crc = Iso3309Crc(packet.datex_Data.data, packet.datex_Data.numbits);


				if (crc != packet_crc)
				{
					ret = -1;
					Dz1Thread_printf("Iso14827C2CAuthMsg_decodeUper() : CRC(Size = %u) = PacketCRC:%04X != Calculated CRC:%04X\n",
									packet.datex_Data.numbits, packet_crc, crc);
					ERR_SET_OUT(errp, EINVAL);
				}
				else
				{
					
					C2CAuthenticatedMessage msg;
					
					ASN1WorkSpace localWS;
					ASN1_INIT_WS_INFO(&localWS);
					pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&localWS);
					
					ASN1_Save_WORKSPACE(&localWS, packet.datex_Data.data, packet.datex_Data.numbits);
					localWS.dataSize = packet.datex_Data.numbits;
					
					if (( ASN1_PER_Align_Dec_C2CAuthenticatedMessage(&localWS, &msg)) < 0) {ERR_SET_OUT(errp, EFAULT);}
					else 
					{	
						//Dz1Thread_printf("Iso14827C2CAuthMsg_decodeAper() : Decoded = ");
						//ASN1_Print_C2CAuthenticatedMessage(&msg, 1);
						
						if ((*errp = Iso14827C2CAuthMsg_fromASN(retMsg, &msg)).code) ERR_SET_OUT(errp, EFAULT);
						
					}
					pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&localWS);
				}
			}
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&pktWS);
	}	
	
	return ret;
}

static ssize_t Iso14827C2CAuthMsg_encodeAperDatex(C2CAuthenticatedMessage *src, u8_t **dst, ASN1WorkSpace *ws, Dz1Error *errp)
{
	ssize_t ret = -1;
	
	if ((ASN1_PER_Align_Enc_C2CAuthenticatedMessage(ws, src)) < 0) { ERR_SET_OUT(errp, EFAULT); }
	else
	{
		DatexDataPacket packet;
		
		uint16_t crc = 0;
		u8_t _crc[2];
		size_t size = ws->buffer.current - ws->buffer.data + (ws->buffer.bitOffset != 8 ? 1 : 0);
		
		ASN1WorkSpace pktWS;
		ASN1_INIT_WS_INFO(&pktWS);
		pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&pktWS);
		
		crc = Iso3309Crc(ws->buffer.data, size);
		_crc[0] = (u8_t)((crc >> 8) & 0x00FF);
		_crc[1] = (u8_t)(crc & 0x00FF);
		
		//Dz1Thread_printf("Iso14827C2CAuthMsg_encodeUper() : CRC(Size = %u) = %02X%02X\n", size, _crc[0], _crc[1]);

		packet.datex_Version_number = DatexDataPacket_datex_Version_number_version1;
		if ((ASN1_SET_DatexDataPacket_datex_Data(&pktWS, &packet, ws->buffer.data, size)) < 0) ERR_SET_OUT(errp, EFAULT);
		else if ((ASN1_SET_DatexDataPacket_datex_Crc_nbr(&pktWS, &packet, _crc, 2)) < 0) ERR_SET_OUT(errp, EFAULT);
		else
		{
			// Encode Packet
			//Dz1Thread_printf("Iso14827C2CAuthMsg_encodeUper() : Data Packet = ");
			//ASN1_Print_DatexDataPacket(&packet, 0);

			if ((ASN1_PER_Align_Enc_DatexDataPacket(&pktWS, &packet)) < 0) ERR_SET_OUT(errp, EFAULT);
			else
			{
				size_t sz = pktWS.buffer.current - pktWS.buffer.data + (pktWS.buffer.bitOffset != 8 ? 1 : 0);
				if ((*dst = (u8_t *)Dz1Malloc((ret = sz), errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else
				{
					// ASN1_Print_DatexDataPacket(&packet, 0);
					memcpy((*dst), pktWS.buffer.data, ret);
				}
			}
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&pktWS);
	}

	return ret;
}
///////////////////////////////////////////////////////////////////////////////
// Iso14827C2CAuthMsg Basic XER CODEC
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Iso14827C2CAuthMsg Canonical XER CODEC
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Iso14827C2CAuthMsg CODEC
///////////////////////////////////////////////////////////////////////////////
ssize_t Iso14827C2CAuthMsg_decodeDatex(Iso14827C2CAuthMsg **retMsg, u8_t *buf, size_t size, Dz1Asn1Codec codec, Dz1Error *err)
{
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
#if defined(GITSN_GENERAL_ASN_TOOL)
	switch(codec)
	{
			case Dz1Asn1Codec_ber:
				if ((ret = Iso14827C2CAuthMsg_decodeBerDatex(retMsg, buf, size, errp)) < 0) ERR_OUT(errp);
				break;
			case Dz1Asn1Codec_aper:
			case Dz1Asn1Codec_uper:
			case Dz1Asn1Codec_xer:
			case Dz1Asn1Codec_cxer:
			case Dz1Asn1Codec_unknown:
			default:
				ERR_SET_OUT(errp, ENOSYS);
				break;
	}
#elif defined(GITSN_NEW_ASN_TOOL)
	switch(codec)
	{
	case Dz1Asn1Codec_ber:
		if ((ret = Iso14827C2CAuthMsg_decodeBerDatex(retMsg, buf, size, errp)) < 0) ERR_OUT(errp);
		break;
	case Dz1Asn1Codec_aper:
		if ((ret = Iso14827C2CAuthMsg_decodeAperDatex(retMsg, buf, size, errp)) < 0) ERR_OUT(errp);
		break;
	case Dz1Asn1Codec_uper:
		if ((ret = Iso14827C2CAuthMsg_decodeUperDatex(retMsg, buf, size, errp)) < 0) ERR_OUT(errp);
		break;
	case Dz1Asn1Codec_xer:
		//if ((ret = Iso14827C2CAuthMsg_decodeBxerDatex(retMsg, buf, size, errp)) < 0) ERR_OUT(errp);
		//break;
	case Dz1Asn1Codec_cxer:
	case Dz1Asn1Codec_unknown:
	default:
		ERR_SET_OUT(errp, ENOSYS);
		break;
	}
#endif
	return ret;
}

ssize_t Iso14827C2CAuthMsg_encodeDatex(Iso14827C2CAuthMsg *src, u8_t **dst, Dz1Asn1Codec codec, Dz1Error *err)
{
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
#if defined(GITSN_GENERAL_ASN_TOOL)
	C2CAuthenticatedMessage_t *_msg = NULL;
	// Convert Iso14827C2CAuthMsg to C2CAuthenticatedMessage_t
	if ((*errp = Iso14827C2CAuthMsg_toASN(&_msg, src)).code) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push((Dz1DelFunc)C2CAuthenticatedMessage_del, (void *)_msg);
		// Dz1Thread_printf("Message Converted = ");
		//C2CAuthenticatedMessage_dump(_msg, 1);
		switch(codec)
		{
			case Dz1Asn1Codec_ber:
				if ((ret = Iso14827C2CAuthMsg_encodeBerDatex(_msg, dst, errp)) < 0) ERR_OUT(errp);
				break;
			case Dz1Asn1Codec_aper:
			case Dz1Asn1Codec_uper:
			case Dz1Asn1Codec_xer:
			case Dz1Asn1Codec_cxer:
			case Dz1Asn1Codec_unknown:
			default:
				ERR_SET_OUT(errp, ENOSYS);
				break;
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)C2CAuthenticatedMessage_del, (void *)_msg);
	}
#elif defined(GITSN_NEW_ASN_TOOL)
	C2CAuthenticatedMessage *_msg = NULL;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	// Convert Iso14827C2CAuthMsg to C2CAuthenticatedMessage_t
	if ((*errp = Iso14827C2CAuthMsg_toASN(&_msg, src, &ws)).code) ERR_OUT(errp);
	else
	{
		//ASN1_Print_C2CAuthenticatedMessage(_msg, 0);
		switch(codec)
		{
		case Dz1Asn1Codec_ber:
			if ((ret = Iso14827C2CAuthMsg_encodeBerDatex(_msg, dst, &ws, errp)) < 0) ERR_OUT(errp);
			break;
		case Dz1Asn1Codec_aper:
			if ((ret = Iso14827C2CAuthMsg_encodeAperDatex(_msg, dst, &ws, errp)) < 0) ERR_OUT(errp);
			break;
		case Dz1Asn1Codec_uper:
			if ((ret = Iso14827C2CAuthMsg_encodeUperDatex(_msg, dst, &ws, errp)) < 0) ERR_OUT(errp);
			break;
		case Dz1Asn1Codec_xer:
			//if ((ret = Iso14827C2CAuthMsg_encodeBxerDatex(_msg, dst, &ws, errp)) < 0) ERR_OUT(errp);
			//break;
		case Dz1Asn1Codec_cxer:
		case Dz1Asn1Codec_unknown:
		default:
			ERR_SET_OUT(errp, ENOSYS);
			break;
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
#endif
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Iso14827DatexDataPacket BER CODEC
///////////////////////////////////////////////////////////////////////////////
static ssize_t Iso14827DatexDataPacket_decodeBer(Iso14827DatexDataPacket **retMsg, u8_t *buf, size_t size, Dz1Error *errp)
{
	ssize_t ret = -1;
 	
	if ( buf == NULL ) ERR_SET_OUT(errp, EINVAL);
	else 
	{
		ssize_t status = 0;
		DatexDataPacket packet;
		ASN1WorkSpace pktWS;
		//int len =0;
		ASN1_INIT_WS_INFO(&pktWS);
		pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&pktWS);

		ASN1_Save_WORKSPACE(&pktWS, buf, size);
		pktWS.dataSize = size;

		if ((status = ASN1_BER_Dec_DatexDataPacket(&pktWS, &packet, size, ASN1EXPL)) < 0)
		{
			ret = status;
			Dz1Thread_printf("!!! Decode Ber Error(%d, %u)\n", status, size);
			Dz1Thread_tprintb(1, buf, size > 64 ? 64 : size, 16, FALSE);
			ERR_SET_OUT(errp, EFAULT);
		}
		else  
		{
			if ((*errp = Iso14827DatexDataPacket_fromASN(retMsg, &packet)).code) ERR_SET_OUT(errp, EFAULT);
			else ret = pktWS.buffer.current - pktWS.buffer.data;
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&pktWS);
	}	
	
	return ret;
}

static ssize_t Iso14827DatexDataPacket_encodeBer(DatexDataPacket *src, u8_t **dst, ASN1WorkSpace *ws, Dz1Error *errp)
{
	ssize_t ret = -1;

	//Dz1Thread_printf("Iso14827C2CAuthMsg_encodeBer() : Source = ");
	//ASN1_Print_C2CAuthenticatedMessage(src, 1);

	if ((ASN1_BER_Enc_DatexDataPacket(ws, src, ASN1EXPL)) < 0) { ERR_SET_OUT(errp, EFAULT); }
	else if (IndefinelenTodefinelen(ws) < 0) ERR_SET_OUT(errp, EFAULT);
	else if ((*dst = (u8_t *)Dz1Malloc((ret = GetDataLength(ws)), errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		// ASN1_Print_DatexDataPacket(&packet, 0);
		memcpy((*dst), ws->buffer.data, ret);
	}

	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Iso14827DatexDataPacket Unaligned PER CODEC
///////////////////////////////////////////////////////////////////////////////
static ssize_t Iso14827DatexDataPacket_decodeUper(Iso14827DatexDataPacket **retMsg, u8_t *buf, size_t size, Dz1Error *errp)
{
	ssize_t ret = -1;
	
	if ( buf == NULL ) ERR_SET_OUT(errp, EINVAL);
	else 
	{
		//int len =0;
		DatexDataPacket packet;

		ASN1WorkSpace pktWS;
		ASN1_INIT_WS_INFO(&pktWS);
		pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&pktWS);
		
		ASN1_Save_WORKSPACE(&pktWS, buf, size);
		pktWS.dataSize = size;
		
		if (( ASN1_PER_UNAlign_Dec_DatexDataPacket(&pktWS, &packet)) < 0) {ERR_SET_OUT(errp, EFAULT);}
		else if ((*errp = Iso14827DatexDataPacket_fromASN(retMsg, &packet)).code) ERR_SET_OUT(errp, EFAULT);
		else ret = pktWS.buffer.current - pktWS.buffer.data + (pktWS.buffer.bitOffset != 8 ? 1 : 0);

		pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&pktWS);
	}	
	
	return ret;
}

static ssize_t Iso14827DatexDataPacket_encodeUper(DatexDataPacket *src, u8_t **dst, ASN1WorkSpace *ws, Dz1Error *errp)
{
	ssize_t ret = -1;
	
	if ((ASN1_PER_UNAlign_Enc_DatexDataPacket(ws, src)) < 0) { ERR_SET_OUT(errp, EFAULT); }
	else
	{
		size_t size = ws->buffer.current - ws->buffer.data + (ws->buffer.bitOffset != 8 ? 1 : 0);
		if ((*dst = (u8_t *)Dz1Malloc((ret = size), errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			// ASN1_Print_DatexDataPacket(&packet, 0);
			memcpy((*dst), ws->buffer.data, ret);
		}
	}

	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Iso14827DatexDataPacket Iso14827DatexDataPacket Aligned PER CODEC
///////////////////////////////////////////////////////////////////////////////
static ssize_t Iso14827DatexDataPacket_decodeAper(Iso14827DatexDataPacket **retMsg, u8_t *buf, size_t size, Dz1Error *errp)
{
	ssize_t ret = -1;
	
	if ( buf == NULL ) ERR_SET_OUT(errp, EINVAL);
	else 
	{
		//int len =0;
		DatexDataPacket packet;

		ASN1WorkSpace pktWS;
		ASN1_INIT_WS_INFO(&pktWS);
		pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&pktWS);
		
		ASN1_Save_WORKSPACE(&pktWS, buf, size);
		pktWS.dataSize = size;
		
		if (( ASN1_PER_Align_Dec_DatexDataPacket(&pktWS, &packet)) < 0) {ERR_SET_OUT(errp, EFAULT);}
		else if ((*errp = Iso14827DatexDataPacket_fromASN(retMsg, &packet)).code) ERR_SET_OUT(errp, EFAULT);
		else ret = pktWS.buffer.current - pktWS.buffer.data + (pktWS.buffer.bitOffset != 8 ? 1 : 0);

		pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&pktWS);
	}	
	
	return ret;
}

static ssize_t Iso14827DatexDataPacket_encodeAper(DatexDataPacket *src, u8_t **dst, ASN1WorkSpace *ws, Dz1Error *errp)
{
	ssize_t ret = -1;
	
	if ((ASN1_PER_Align_Enc_DatexDataPacket(ws, src)) < 0) { ERR_SET_OUT(errp, EFAULT); }
	else
	{
		size_t size = ws->buffer.current - ws->buffer.data + (ws->buffer.bitOffset != 8 ? 1 : 0);
		if ((*dst = (u8_t *)Dz1Malloc((ret = size), errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			// ASN1_Print_DatexDataPacket(&packet, 0);
			memcpy((*dst), ws->buffer.data, ret);
		}
	}

	return ret;
}
///////////////////////////////////////////////////////////////////////////////
// Iso14827DatexDataPacket CODEC
///////////////////////////////////////////////////////////////////////////////
ssize_t Iso14827DatexDataPacket_decode(Iso14827DatexDataPacket **retMsg, u8_t *buf, size_t size, Dz1Asn1Codec codec, Dz1Error *err)
{
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
#if defined(GITSN_GENERAL_ASN_TOOL)
#elif defined(GITSN_NEW_ASN_TOOL)
	switch(codec)
	{
	case Dz1Asn1Codec_ber:
		if ((ret = Iso14827DatexDataPacket_decodeBer(retMsg, buf, size, errp)) < 0) ERR_OUT(errp);
		break;
	case Dz1Asn1Codec_aper:
		if ((ret = Iso14827DatexDataPacket_decodeAper(retMsg, buf, size, errp)) < 0) ERR_OUT(errp);
		break;
	case Dz1Asn1Codec_uper:
		if ((ret = Iso14827DatexDataPacket_decodeUper(retMsg, buf, size, errp)) < 0) ERR_OUT(errp);
		break;
	case Dz1Asn1Codec_xer:
		//if ((ret = Iso14827DatexDataPacket_decodeBxer(retMsg, buf, size, errp)) < 0) ERR_OUT(errp);
		//break;
	case Dz1Asn1Codec_cxer:
	case Dz1Asn1Codec_unknown:
	default:
		ERR_SET_OUT(errp, ENOSYS);
		break;
	}
#endif
	return ret;
}

ssize_t Iso14827DatexDataPacket_encode(Iso14827DatexDataPacket *src, u8_t **dst, Dz1Asn1Codec codec, Dz1Error *err)
{
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
#if defined(GITSN_GENERAL_ASN_TOOL)
#elif defined(GITSN_NEW_ASN_TOOL)
	DatexDataPacket *_msg = NULL;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	// Convert Iso14827C2CAuthMsg to C2CAuthenticatedMessage_t
	if ((*errp = Iso14827DatexDataPacket_toASN(&_msg, src, &ws)).code) ERR_OUT(errp);
	else
	{
		Dz1Thread_printf("Iso14827DatexDataPacket_encode() : Msg = ");
		Iso14827DatexDataPacket_dump(src, 0);

		switch(codec)
		{
		case Dz1Asn1Codec_ber:
			if ((ret = Iso14827DatexDataPacket_encodeBer(_msg, dst, &ws, errp)) < 0) ERR_OUT(errp);
			break;
		case Dz1Asn1Codec_aper:
			if ((ret = Iso14827DatexDataPacket_encodeAper(_msg, dst, &ws, errp)) < 0) ERR_OUT(errp);
			break;
		case Dz1Asn1Codec_uper:
			if ((ret = Iso14827DatexDataPacket_encodeUper(_msg, dst, &ws, errp)) < 0) ERR_OUT(errp);
			break;
		case Dz1Asn1Codec_xer:
			//if ((ret = Iso14827DatexDataPacket_encodeBxer(_msg, dst, &ws, errp)) < 0) ERR_OUT(errp);
			//break;
		case Dz1Asn1Codec_cxer:
		case Dz1Asn1Codec_unknown:
		default:
			ERR_SET_OUT(errp, ENOSYS);
			break;
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
#endif
	return ret;
}



///////////////////////////////////////////////////////////////////////////////
// Iso14827C2CAuthMsg BER CODEC
///////////////////////////////////////////////////////////////////////////////
static ssize_t Iso14827C2CAuthMsg_decodeBer(Iso14827C2CAuthMsg **retMsg, u8_t *buf, size_t size, Dz1Error *errp)
{
	ssize_t ret = -1;
 	
	if ( buf == NULL ) ERR_SET_OUT(errp, EINVAL);
	else 
	{
		C2CAuthenticatedMessage msg;
		
 		ASN1WorkSpace localWS;
 		ASN1_INIT_WS_INFO(&localWS);
		pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&localWS);

		ASN1_Save_WORKSPACE(&localWS, buf, size);
		localWS.dataSize = size;

 		if (ASN1_BER_Dec_C2CAuthenticatedMessage(&localWS, &msg, size, ASN1EXPL) < 0)
		{
			ERR_SET_OUT(errp, EFAULT);
		}
 		else 
 		{	
			//Dz1Thread_printf("Iso14827C2CAuthMsg_decodeBer() : Decoded = ");
			//ASN1_Print_C2CAuthenticatedMessage(&msg, 1);
			ret = localWS.buffer.current - localWS.buffer.data;
 			if ((*errp = Iso14827C2CAuthMsg_fromASN(retMsg, &msg)).code) ERR_SET_OUT(errp, EFAULT);
 			
 		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&localWS);
	}	
	return ret;
}

static ssize_t Iso14827C2CAuthMsg_encodeBer(C2CAuthenticatedMessage *src, u8_t **dst, ASN1WorkSpace *ws, Dz1Error *errp)
{
	ssize_t ret = -1;

	//Dz1Thread_printf("Iso14827C2CAuthMsg_encodeBer() : Source = ");
	//ASN1_Print_C2CAuthenticatedMessage(src, 1);

	if ((ASN1_BER_Enc_C2CAuthenticatedMessage(ws, src, ASN1EXPL)) < 0) { ERR_SET_OUT(errp, EFAULT); }
	else if (IndefinelenTodefinelen(ws) < 0) ERR_SET_OUT(errp, EFAULT);
	else if ((*dst = (u8_t *)Dz1Malloc((ret = GetDataLength(ws)), errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		// ASN1_Print_DatexDataPacket(&packet, 0);
		memcpy((*dst), ws->buffer.data, ret);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Iso14827C2CAuthMsg Unaligned PER CODEC
///////////////////////////////////////////////////////////////////////////////
static ssize_t Iso14827C2CAuthMsg_decodeUper(Iso14827C2CAuthMsg **retMsg, u8_t *buf, size_t size, Dz1Error *errp)
{
	ssize_t ret = -1;
	
	if ( buf == NULL ) ERR_SET_OUT(errp, EINVAL);
	else 
	{
		C2CAuthenticatedMessage msg;
		
		ASN1WorkSpace localWS;
		ASN1_INIT_WS_INFO(&localWS);
		pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&localWS);
		
		ASN1_Save_WORKSPACE(&localWS, buf, size);
		localWS.dataSize = size;
		
		if (( ASN1_PER_UNAlign_Dec_C2CAuthenticatedMessage(&localWS, &msg)) < 0) {ERR_SET_OUT(errp, EFAULT);}
		else 
		{	
//			Dz1Thread_printf("Iso14827C2CAuthMsg_decodeUper() : Decoded = ");
//			ASN1_Print_C2CAuthenticatedMessage(&msg, 1);
			ret = localWS.buffer.current - localWS.buffer.data + (localWS.buffer.bitOffset != 8 ? 1 : 0);
			if ((*errp = Iso14827C2CAuthMsg_fromASN(retMsg, &msg)).code) ERR_SET_OUT(errp, EFAULT);
			
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&localWS);
	}	
	
	return ret;
}

static ssize_t Iso14827C2CAuthMsg_encodeUper(C2CAuthenticatedMessage *src, u8_t **dst, ASN1WorkSpace *ws, Dz1Error *errp)
{
	ssize_t ret = -1;
	
//	Dz1Thread_printf("Iso14827C2CAuthMsg_encodeUper() : Source = ");
//	ASN1_Print_C2CAuthenticatedMessage(src, 1);

	if ((ASN1_PER_UNAlign_Enc_C2CAuthenticatedMessage(ws, src)) < 0) { ERR_SET_OUT(errp, EFAULT); }
	{
		size_t size = ws->buffer.current - ws->buffer.data + (ws->buffer.bitOffset != 8 ? 1 : 0);
		if ((*dst = (u8_t *)Dz1Malloc((ret = size), errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			// ASN1_Print_DatexDataPacket(&packet, 0);
			memcpy((*dst), ws->buffer.data, ret);
		}
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Iso14827C2CAuthMsg Aligned PER CODEC
///////////////////////////////////////////////////////////////////////////////
static ssize_t Iso14827C2CAuthMsg_decodeAper(Iso14827C2CAuthMsg **retMsg, u8_t *buf, size_t size, Dz1Error *errp)
{
	ssize_t ret = -1;
	
	if ( buf == NULL ) ERR_SET_OUT(errp, EINVAL);
	else 
	{
		C2CAuthenticatedMessage msg;
		
		ASN1WorkSpace localWS;
		ASN1_INIT_WS_INFO(&localWS);
		pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&localWS);
		
		ASN1_Save_WORKSPACE(&localWS, buf, size);
		localWS.dataSize = size;
		
		if (ASN1_PER_Align_Dec_C2CAuthenticatedMessage(&localWS, &msg) < 0) {ERR_SET_OUT(errp, EFAULT);}
		else 
		{	
			//Dz1Thread_printf("Iso14827C2CAuthMsg_decodeAper() : Decoded = ");
			//ASN1_Print_C2CAuthenticatedMessage(&msg, 1);
			ret = localWS.buffer.current - localWS.buffer.data + (localWS.buffer.bitOffset != 8 ? 1 : 0);
			if ((*errp = Iso14827C2CAuthMsg_fromASN(retMsg, &msg)).code) ERR_SET_OUT(errp, EFAULT);
			
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&localWS);
	}	
	return ret;
}

static ssize_t Iso14827C2CAuthMsg_encodeAper(C2CAuthenticatedMessage *src, u8_t **dst, ASN1WorkSpace *ws, Dz1Error *errp)
{
	ssize_t ret = -1;
	
	if ((ASN1_PER_Align_Enc_C2CAuthenticatedMessage(ws, src)) < 0) { ERR_SET_OUT(errp, EFAULT); }
	else
	{
		size_t size = ws->buffer.current - ws->buffer.data + (ws->buffer.bitOffset != 8 ? 1 : 0);
		if ((*dst = (u8_t *)Dz1Malloc((ret = size), errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			memcpy((*dst), ws->buffer.data, ret);
		}
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Iso14827C2CAuthMsg Basic XER CODEC
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Iso14827C2CAuthMsg Canonical XER CODEC
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Iso14827C2CAuthMsg CODEC
///////////////////////////////////////////////////////////////////////////////
ssize_t Iso14827C2CAuthMsg_decode(Iso14827C2CAuthMsg **retMsg, u8_t *buf, size_t size, Dz1Asn1Codec codec, Dz1Error *err)
{
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
#if defined(GITSN_GENERAL_ASN_TOOL)
	switch(codec)
	{
			case Dz1Asn1Codec_ber:
				if ((ret = Iso14827C2CAuthMsg_decodeBer(retMsg, buf, size, errp)) < 0) ERR_OUT(errp);
				break;
			case Dz1Asn1Codec_aper:
			case Dz1Asn1Codec_uper:
			case Dz1Asn1Codec_xer:
			case Dz1Asn1Codec_cxer:
			case Dz1Asn1Codec_unknown:
			default:
				ERR_SET_OUT(errp, ENOSYS);
				break;
	}
#elif defined(GITSN_NEW_ASN_TOOL)
	switch(codec)
	{
	case Dz1Asn1Codec_ber:
		if ((ret = Iso14827C2CAuthMsg_decodeBer(retMsg, buf, size, errp)) < 0) ERR_OUT(errp);
		break;
	case Dz1Asn1Codec_aper:
		if ((ret = Iso14827C2CAuthMsg_decodeAper(retMsg, buf, size, errp)) < 0) ERR_OUT(errp);
		break;
	case Dz1Asn1Codec_uper:
		if ((ret = Iso14827C2CAuthMsg_decodeUper(retMsg, buf, size, errp)) < 0) ERR_OUT(errp);
		break;
	case Dz1Asn1Codec_xer:
		//if ((ret = Iso14827C2CAuthMsg_decodeBxerDatex(retMsg, buf, size, errp)) < 0) ERR_OUT(errp);
		//break;
	case Dz1Asn1Codec_cxer:
	case Dz1Asn1Codec_unknown:
	default:
		ERR_SET_OUT(errp, ENOSYS);
		break;
	}
#endif
	return ret;
}

ssize_t Iso14827C2CAuthMsg_encode(Iso14827C2CAuthMsg *src, u8_t **dst, Dz1Asn1Codec codec, Dz1Error *err)
{
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
#if defined(GITSN_GENERAL_ASN_TOOL)
	C2CAuthenticatedMessage_t *_msg = NULL;
	// Convert Iso14827C2CAuthMsg to C2CAuthenticatedMessage_t
	if ((*errp = Iso14827C2CAuthMsg_toASN(&_msg, src)).code) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push((Dz1DelFunc)C2CAuthenticatedMessage_del, (void *)_msg);
		// Dz1Thread_printf("Message Converted = ");
		//C2CAuthenticatedMessage_dump(_msg, 1);
		switch(codec)
		{
			case Dz1Asn1Codec_ber:
				if ((ret = Iso14827C2CAuthMsg_encodeBer(_msg, dst, errp)) < 0) ERR_OUT(errp);
				break;
			case Dz1Asn1Codec_aper:
			case Dz1Asn1Codec_uper:
			case Dz1Asn1Codec_xer:
			case Dz1Asn1Codec_cxer:
			case Dz1Asn1Codec_unknown:
			default:
				ERR_SET_OUT(errp, ENOSYS);
				break;
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)C2CAuthenticatedMessage_del, (void *)_msg);
	}
#elif defined(GITSN_NEW_ASN_TOOL)
	C2CAuthenticatedMessage *_msg = NULL;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	// Convert Iso14827C2CAuthMsg to C2CAuthenticatedMessage_t
	if ((*errp = Iso14827C2CAuthMsg_toASN(&_msg, src, &ws)).code) ERR_OUT(errp);
	else
	{
		Dz1Thread_printf("Iso14827C2CAuthMsg_encodeDatex() : Msg = ");
		Iso14827C2CAuthMsg_dump(src, 0);
		//ASN1_Print_C2CAuthenticatedMessage(_msg, 0);

		switch(codec)
		{
		case Dz1Asn1Codec_ber:
			if ((ret = Iso14827C2CAuthMsg_encodeBer(_msg, dst, &ws, errp)) < 0) ERR_OUT(errp);
			break;
		case Dz1Asn1Codec_aper:
			if ((ret = Iso14827C2CAuthMsg_encodeAper(_msg, dst, &ws, errp)) < 0) ERR_OUT(errp);
			break;
		case Dz1Asn1Codec_uper:
			if ((ret = Iso14827C2CAuthMsg_encodeUper(_msg, dst, &ws, errp)) < 0) ERR_OUT(errp);
			break;
		case Dz1Asn1Codec_xer:
			//if ((ret = Iso14827C2CAuthMsg_encodeBxerDatex(_msg, dst, &ws, errp)) < 0) ERR_OUT(errp);
			//break;
		case Dz1Asn1Codec_cxer:
		case Dz1Asn1Codec_unknown:
		default:
			ERR_SET_OUT(errp, ENOSYS);
			break;
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
#endif
	return ret;
}



#endif
