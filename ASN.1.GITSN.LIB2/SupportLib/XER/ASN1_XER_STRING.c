#include "ASN1_XER_STRING.h"
ASNUINT8 *change_word[]={
/*0*/ "#",
/*1*/ "#",
/*2*/ "#",
/*3*/ "#",
/*4*/ "#",
/*5*/ "#",
/*6*/ "#",
/*7*/ "#",
/*8*/ "#",
/*9*/ "#",
/*10*/ "#",
/*11*/ "#",
/*12*/ "#",
/*13*/ "#",
/*14*/ "#",
/*15*/ "#",
/*16*/ "#",
/*17*/ "#",
/*18*/ "#",
/*19*/ "#",
/*20*/ "#",
/*21*/ "#",
/*22*/ "#",
/*23*/ "#",
/*24*/ "#",
/*25*/ "#",
/*26*/ "#",
/*27*/ "#",
/*28*/ "#",
/*29*/ "#",
/*30*/ "#",
/*31*/ "#",
/*32*/ "#",
/*33*/ "#",
/*34*/ "#",
/*35*/ "#",
/*36*/ "#",
/*37*/ "#",
/*38*/ "&amp;",
/*39*/ "#",
/*40*/ "#",
/*41*/ "#",
/*42*/ "#",
/*43*/ "#",
/*44*/ "#",
/*45*/ "#",
/*46*/ "#",
/*47*/ "#",
/*48*/ "#",
/*49*/ "#",
/*50*/ "#",
/*51*/ "#",
/*52*/ "#",
/*53*/ "#",
/*54*/ "#",
/*55*/ "#",
/*56*/ "#",
/*57*/ "#",
/*58*/ "#",
/*59*/ "#",
/*60*/ "&lt;",
/*61*/ "#",
/*62*/ "&gt;",
/*63*/ "#",
/*64*/ "#",
/*65*/ "#",
/*66*/ "#",
/*67*/ "#",
/*68*/ "#",
/*69*/ "#",
/*70*/ "#",
/*71*/ "#",
/*72*/ "#",
/*73*/ "#",
/*74*/ "#",
/*75*/ "#",
/*76*/ "#",
/*77*/ "#",
/*78*/ "#",
/*79*/ "#",
/*80*/ "#",
/*81*/ "#",
/*82*/ "#",
/*83*/ "#",
/*84*/ "#",
/*85*/ "#",
/*86*/ "#",
/*87*/ "#",
/*88*/ "#",
/*89*/ "#",
/*90*/ "#",
/*91*/ "#",
/*92*/ "#",
/*93*/ "#",
/*94*/ "#",
/*95*/ "#",
/*96*/ "#",
/*97*/ "#",
/*98*/ "#",
/*99*/ "#",
/*100*/ "#",
/*101*/ "#",
/*102*/ "#",
/*103*/ "#",
/*104*/ "#",
/*105*/ "#",
/*106*/ "#",
/*107*/ "#",
/*108*/ "#",
/*109*/ "#",
/*110*/ "#",
/*111*/ "#",
/*112*/ "#",
/*113*/ "#",
/*114*/ "#",
/*115*/ "#",
/*116*/ "#",
/*117*/ "#",
/*118*/ "#",
/*119*/ "#",
/*120*/ "#",
/*121*/ "#",
/*122*/ "#",
/*123*/ "#",
/*124*/ "#",
/*125*/ "#",
/*126*/ "#",
/*127*/ "#",
/*128*/ "#",
/*129*/ "#",
/*130*/ "#",
/*131*/ "#",
/*132*/ "#",
/*133*/ "#",
/*134*/ "#",
/*135*/ "#",
/*136*/ "#",
/*137*/ "#",
/*138*/ "#",
/*139*/ "#",
/*140*/ "#",
/*141*/ "#",
/*142*/ "#",
/*143*/ "#",
/*144*/ "#",
/*145*/ "#",
/*146*/ "#",
/*147*/ "#",
/*148*/ "#",
/*149*/ "#",
/*150*/ "#",
/*151*/ "#",
/*152*/ "#",
/*153*/ "#",
/*154*/ "#",
/*155*/ "#",
/*156*/ "#",
/*157*/ "#",
/*158*/ "#",
/*159*/ "#",
/*160*/ "#",
/*161*/ "#",
/*162*/ "#",
/*163*/ "#",
/*164*/ "#",
/*165*/ "#",
/*166*/ "#",
/*167*/ "#",
/*168*/ "#",
/*169*/ "#",
/*170*/ "#",
/*171*/ "#",
/*172*/ "#",
/*173*/ "#",
/*174*/ "#",
/*175*/ "#",
/*176*/ "#",
/*177*/ "#",
/*178*/ "#",
/*179*/ "#",
/*180*/ "#",
/*181*/ "#",
/*182*/ "#",
/*183*/ "#",
/*184*/ "#",
/*185*/ "#",
/*186*/ "#",
/*187*/ "#",
/*188*/ "#",
/*189*/ "#",
/*190*/ "#",
/*191*/ "#",
/*192*/ "#",
/*193*/ "#",
/*194*/ "#",
/*195*/ "#",
/*196*/ "#",
/*197*/ "#",
/*198*/ "#",
/*199*/ "#",
/*200*/ "#",
/*201*/ "#",
/*202*/ "#",
/*203*/ "#",
/*204*/ "#",
/*205*/ "#",
/*206*/ "#",
/*207*/ "#",
/*208*/ "#",
/*209*/ "#",
/*210*/ "#",
/*211*/ "#",
/*212*/ "#",
/*213*/ "#",
/*214*/ "#",
/*215*/ "#",
/*216*/ "#",
/*217*/ "#",
/*218*/ "#",
/*219*/ "#",
/*220*/ "#",
/*221*/ "#",
/*222*/ "#",
/*223*/ "#",
/*224*/ "#",
/*225*/ "#",
/*226*/ "#",
/*227*/ "#",
/*228*/ "#",
/*229*/ "#",
/*230*/ "#",
/*231*/ "#",
/*232*/ "#",
/*233*/ "#",
/*234*/ "#",
/*235*/ "#",
/*236*/ "#",
/*237*/ "#",
/*238*/ "#",
/*239*/ "#",
/*240*/ "#",
/*241*/ "#",
/*242*/ "#",
/*243*/ "#",
/*244*/ "#",
/*245*/ "#",
/*246*/ "#",
/*247*/ "#",
/*248*/ "#",
/*249*/ "#",
/*250*/ "#",
/*251*/ "#",
/*252*/ "#",
/*253*/ "#",
/*254*/ "#",
/*255*/ "#",
};
ASN1_CPPLINK ASNINT32 ASN1_XER_Enc_ASNSTRING_Value(ASN1WorkSpace * ws,ASNSTRING *tvalue)
{
//	ASNUINT8 temp_value[128];
	ASNUINT8* temp_char = tvalue->asnstring;
	ASNINT32  char_lenght = tvalue->nchar;

	while(char_lenght){
		if (*change_word[*temp_char] != '#'){
			ASN1_XER_FillBuffer(ws,change_word[*temp_char], (ASNUINT32)strlen(change_word[*temp_char]));
		}
		else{
			ASN1_XER_FillBuffer(ws,temp_char,1);
		}
		temp_char++;
		char_lenght--;
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CONV(ASNUINT8* value)
{
//	ASNUINT8 temp_value[128];
	ASNINT32 i=0;
	while(strcmp(value,change_word[i])){
		i++;
	}
	return i;
}
ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_ASNSTRING_Value(ASN1WorkSpace * ws, ASNSTRING *value)
{
	ASNUINT8 temp_value[128];
	ASNINT32 i = 0,j = 0,k = 0;
	ASNINT32 memory = 1;
	

	value->asnstring = mpool_malloc(ws->Pmemory,memory);
	value->nchar = 0;

	memset(temp_value,0x00,128);
	
	while(!(*ws->buffer.current == '<'|| *ws->buffer.current == '/')) {
		if(*ws->buffer.current == '&'){
			while (*ws->buffer.current != ';'){
				temp_value[j] = *ws->buffer.current;
				j++;
				ws->buffer.current++;
			}
			temp_value[j] = *ws->buffer.current;
			ws->buffer.current++;
			value->asnstring = mpool_realloc(ws->Pmemory,
											 value->asnstring,
											 ++memory);
			value->asnstring[k++] = ASN1_XER_CONV(temp_value);
			value->nchar++;
			j=0;
			memset(temp_value,0x00,128);
		}
		else if(*ws->buffer.current == '<'){
			while (*ws->buffer.current != '>'){
				temp_value[j] = *ws->buffer.current;
				j++;
				ws->buffer.current++;
			}
			ws->buffer.current++;
			value->asnstring = mpool_realloc(ws->Pmemory,
											 value->asnstring,
											 ++memory);
			value->asnstring[k++] = ASN1_XER_CONV(temp_value);
			value->nchar++;
			memset(temp_value,0x00,128);
		}

		else{
			value->asnstring = mpool_realloc(ws->Pmemory,
											 value->asnstring,
											 ++memory);
			value->asnstring[k++] = *ws->buffer.current;
			value->nchar++;
			ws->buffer.current++;
		}
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_ASNSTRING(ASN1WorkSpace * ws, ASNSTRING *tvalue, 
										ASNUINT8 *name,ASNINT32 tab_value)
										
{
	if (tvalue->nchar == 0){
		ASN1_XER_Enc_Backslash_Name(ws,name);
		return 0;
	}
	ASN1_XER_Enc_Start_Name(ws,name);
	ASN1_XER_Enc_ASNSTRING_Value(ws,tvalue);
	ASN1_XER_Enc_End_Name(ws,name);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_ASNSTRING(ASN1WorkSpace * ws, ASNSTRING *tvalue,
									  ASNUINT8 *name,ASNINT32 tab_value)
									
{
	ASN1_XER_Tab(ws,tab_value);
	ASN1_XER_CANONICAL_Enc_ASNSTRING(ws,tvalue,name,tab_value);
	ASN1_XER_Enter(ws,1);
	return 0;
	
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_ASNSTRING(ASN1WorkSpace * ws, ASNSTRING *value,
										ASNUINT8 *name,ASNINT32 tab_value)
{
	if (6==ASN1_XER_Dec_Name(ws)){
		value->nchar = 0;
		return 0;
	}
	ASN1_XER_Dec_ASNSTRING_Value(ws,value);
	ASN1_XER_Dec_Name(ws);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_ASNSTRING(ASN1WorkSpace * ws, ASNSTRING *value,
									ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Dec_Format(ws);
	ASN1_XER_CANONICAL_Dec_ASNSTRING(ws,value,name,tab_value);
/*	ASN1_XER_Dec_Format(ws);*/
	return 0;
}
