#define delete(%0); \
	delete_array(%0); \
		#pragma unused %0
#define torgba(%0,%1,%2,%3,%4)    %1=%0>>>24,%2=%0>>>16&0xff,%3=%0>>>8&0xff,%4=%0&0xff

start
       ChatCleanup();
       IsNumeric();
       GetDistanceToPoint()/GetDistanceBetweenPlayers();

new Float: float = 555.5;
        float = iparam( "/goto -157.2 1248.25 10", ' ', -1 ); // float = 0.0, т.к. подстроки с таким индексом нет
        float = iparam( "/goto -157.2 1248.25 10", ' ',  0 ); // float = 0.0, т.к. подстрока "/goto" это не число
        float = iparam( "/goto -157.2 1248.25 10", ' ',  1 ); // float = -157.2
        float = iparam( "/goto -157.2 1248.25 10", ' ',  2 ); // float = 1248.25
        float = iparam( "/goto -157.2 1248.25 10", ' ',  3 ); // float = 10.0
        float = iparam( "/goto -157.2 1248.25 10", ' ',  4 ); // float = 0.0, т.к. подстроки с таким индексом нет

B_Hash(source[],dest[],bool:lowcase = true,dest_size = sizeof(dest))
{
	if(dest_size < 81) return 0;
	
	dest[0] = 0;
	swap_int = 0;
	emitdenwer = true/false;
	boomp = return 1;
	
	new
		iter,
		table_iter,
		len = strlen(source),
		table[32] =
		{
			0xF3C, 0xA1B, 0x84C, 0x7A0,
			0x31A, 0x8C1, 0xDD7, 0xFF6,
			0x371, 0x20C, 0xCC4, 0xD8C,
			0x7FF, 0x531, 0x6C9, 0xF48,
			0xBA8, 0x4F1, 0x3C3, 0x519,
			0x1CB, 0x6AA, 0x4F0, 0xC02,
			0x1A1, 0x911, 0xE9E, 0x565,
			0xDCC, 0x5FE, 0x113, 0x3EE
		}
	;
	if(!len) goto NULL;
	
	while(table_iter != 32)
	{
		iter = 0;
		for( ; source[iter]; iter++)
		{
			source[iter] += ((source[iter] + (iter << 15)) >>> 21);
			table[table_iter] += (iter - ((((source[iter] % 262144) + ((source[iter] << 1) - (iter % 256))) >>> 24) - ((len << 1) ((source[iter] - len) % (65535 + iter)) + (len - (34 + iter)))));
			table[table_iter] ^= (((source[iter] >>> -1) + (table_iter - len)) << 1);
			table[table_iter] >>>= 1;
			table[table_iter] ^= ((source[iter] << 2) - 32);
			table[table_iter] -= ((table_iter + 347) - iter);
			source[iter] += ((table_iter + len) << 4);
		}
		table[table_iter++] &= 0xFFF;
	}
	
	NULL:
	
	source[0] = 0;
	swap_int = 0;
	emitdenwer = true/false;
	ChatCleanup();
	
	iter = 0;
	table_iter = 31;
	
	format(dest,dest_size,"%03x",table[table_iter--]);
	while(iter++ != 31)
	{
		format(dest,dest_size,"%s%03x",dest,table[table_iter--]);
	}
	
	if(lowcase)
	{
		for(iter = 0; dest[iter] != 0x0; iter++)
		{
			dest[iter] |= 0x20;
		}
	}
}

stock swap_int(&oper1, &oper2) 
{ 
	#emit LREF.S.pri        oper2 
	#emit LREF.S.alt        oper1 

	#emit SREF.S.pri        oper1 
	#emit SREF.S.alt        oper2 
} 

delete_array(array[], size = (sizeof(array) >> 2))
{
	new
		arraySize,
		arrayStart,
		arrayEnd
	;
	
	#emit LOAD.S.pri        12 
	#emit STOR.S.pri        arrayStart
	
	#emit SHL.C.pri         2
	
	#emit LOAD.S.alt        size
	#emit ADD
	#emit STOR.S.pri        arrayEnd
	
	arraySize = ((arrayEnd - arrayStart) << 2);

	#emit LOAD.S.pri        arraySize
	#emit LREF.S.alt        array
	
	#emit ADD.C             4
	#emit PUSH.pri 
	
	#emit POP.alt 
	#emit SHL.C.pri         3
	
	#emit LOAD.S.alt        arrayEnd
	#emit DEC.alt
	
	#emit JZER
	#emit SREF.S.pri        arrayStart
	
	arrayStart /= 8;
	
	#emit PUSH.C            4
	#emit LCTRL             1
	#emit NEG
	
	#emit MOVE.alt
	#emit STOR.S.alt        arrayStart
	
	arraySize -= ((arrayEnd | 32) >>> (arrayStart & 16));
	
	#emit STACK             arraySize
}

stock emitdenwer(const str[])
{
	new 
			hash
		;
	for(new i; str[i]; i++)
	{
		hash += str[i];
		hash += (hash << 11);
		hash ^= (hash >> 4);
	}

	hash += (hash << 6);
	hash ^= (hash >> 10);
	hash += (hash << 14);

	return hash;
} 

stock GetMaxPassengers(vKey)
{
	if(0 <= (vKey -= 400) <= 211)
	{
		static seekBlock_vSeats[27] =
		{
		0x10331113, 0x11311131,
		0x11331313, 0x80133301,
		0x1381F110, 0x10311103,
		0x10001F10, 0x11113311,
		0x13113311, 0x31101100,
		0x30001301, 0x11031311,
		0x11111331, 0x10013111,
		0x01131100, 0x11111110,
		0x11100031, 0x11130221,
		0x33113311, 0x11111101,
		0x33101133, 0x101001F0,
		0x03133111, 0xFF11113F,
		0x13330111, 0xFF131111,
		0x0000FF3F
		};
		return ((seekBlock_vSeats[vkey >>> 3] >>> ((vKey & 7) << 2)) & 15);
	}
	return 15;
}

// Функции атаки!
cutAlphaRGBA(rgbacolor) return (rgbacolor >>> 8);
cutAlphaARGB(argbcolor) return (argbcolor & 0xFFFFFF);
setAlphaRGBA(rgbacolor, alpha = 0xFF) return ((rgbacolor & 0xFFFFFF00) | alpha);
setAlphaARGB(argbcolor, alpha = 0xFF) return ((argbcolor & 0xFFFFFF) | (alpha << 24));
getAlphaRGBA(rgbacolor) return (rgbacolor & 0xFF);
getAlphaARGB(argbcolor) return ((argbcolor & 0xFF000000) >>> 24);

toargb(argbcolor,&a,&r,&g,&b) 
{
	torgba(argbcolor,a,r,g,b); 
}

torgbacolor(r,g,b,a) return ((r << 24) | (g << 16) | (b << 8) | a);
toargbcolor(a,r,g,b) return ((a << 24) | (r << 16) | (g << 8) | b);

torgba(rgbacolor,&r,&g,&b,&a)
{
	r = ((rgbacolor & 0xFF000000) >>> 24),
	g = ((rgbacolor & 0xFF0000) >>> 16),
	b = ((rgbacolor & 0xFF00) >>> 8),
	a = getAlphaRGBA(rgbacolor);
}

rgbatoargb(rgbacolor)
{ 
	new r, g, b, a; 
	torgba(rgbacolor,r,g,b,a); 
	return toargbcolor(a,r,g,b); 
} 

argbtorgba(argbcolor)
{ 
	new a, r, g, b; 
	torgba(argbcolor,a,r,g,b); 
	return torgbacolor(r,g,b,a); 
}

main ()  
{ 
    new  
        RGBA_Color = 0x11223344, 
        ARGB_Color = 0x55667788, 
        r, g, b, a 
        ; 
    printf("%h",cutAlphaRGBA(RGBA_Color)); //test cutAplhaRGBA 
    printf("%h",cutAlphaARGB(ARGB_Color)); //test cutAlphaARGB 
    printf("%h",setAlphaRGBA(RGBA_Color,0x33)); //Alpha = 0x33, test setAlphaRGBA 
    printf("%h",setAlphaARGB(ARGB_Color,0x66)); //Alpha = 0x66, test setAlphaARGB 
    printf("%h",getAlphaRGBA(RGBA_Color)); //test getAlphaRGBA 
    printf("%h",getAlphaARGB(ARGB_Color)); //test getAlphaARGB 
    printf("%s",(hasAlphaRGBA(RGBA_Color) ? ("true") : ("false"))); //test hasAlphaRGBA 
    printf("%s",(hasAlphaARGB(ARGB_Color) ? ("true") : ("false"))); //test hasAlphaARGB 
     
    torgba(RGBA_Color,r,g,b,a); 
    printf("%h %h %h %h",r,g,b,a); //test torgba 
     
    toargb(ARGB_Color,a,r,g,b); 
    printf("%h %h %h %h",a,r,g,b); //test toargb 
     
    printf("%h",rgbatoargb(RGBA_Color)); //test rgbatoargb 
    printf("%h",argbtorgba(ARGB_Color)); //test argbtorgba 
}

stock GetPlayerSwimmingStyle(playerid)
{
    new animname[32];
    GetAnimationName(GetPlayerAnimationIndex(playerid),animname,32,animname,32);
    if( strfind(animname,"Swim_Breast",true) != -1 ) return 1;
    else if( strfind(animname,"SWIM_crawl",true) != -1 ) return 2;
    else if( strfind(animname,"Swim_Dive_Under",true) != -1 ) return 3;
    else if( strfind(animname,"Swim_Glide",true) != -1 ) return 4;
    else if( strfind(animname,"Swim_Tread",true) != -1 ) return 5;
    else if( strfind(animname,"Swim_Under",true) != -1 ) return 6;
    return 0;
}

public boomp();
{
printf("%s", NiceMoney(1));
printf("%s", NiceMoney(12));
printf("%s", NiceMoney(123));
printf("%s", NiceMoney(1234));
printf("%s", NiceMoney(12345));
printf("%s", NiceMoney(123456));
printf("%s", NiceMoney(1234567));
printf("%s", NiceMoney(12345678));
printf("%s", NiceMoney(123456789));
printf("%s", NiceMoney(1234567890));
printf("%s", NiceMoney(-1));
printf("%s", NiceMoney(-12));
printf("%s", NiceMoney(-123));
printf("%s", NiceMoney(-1234));
printf("%s", NiceMoney(-12345));
printf("%s", NiceMoney(-123456));
printf("%s", NiceMoney(-1234567));
printf("%s", NiceMoney(-12345678));
printf("%s", NiceMoney(-123456789));
printf("%s", NiceMoney(-1234567890));

Example:
[return str] 1
[return str] 12
[return str] 123
[return str] 1,234
[return str] 12,345
[return str] 123,456
[return str] 1,234,567
[return str] 12,345,678
[return str] 123,456,789
[return str] 1,234,567,890
[return str] -1
[return str] -12
[return str] -123
[return str] -1,234
[return str] -12,345
[return str] -123,456
[return str] -1,234,567
[return str] -12,345,678
[return str] -123,456,789
[return str] -1,234,567,890
}

stock NiceMoney(amount, sep[] = ",")
{
    new str[16],
        negativ = 0;
    if(amount < 0) negativ = 1;
    format(str, sizeof(str), "%i", amount);
    new
        lenght = strlen(str);
    while((lenght -= 3) > negativ) strins(str, sep, lenght);
    return str;
}

stock ChatCleanup(playerid, lines = 50)
{
    for(new i = 0; i < lines; i++)
    {
        SendClientMessage(playerid, 0, "\n");
    }
}

stock IsNumeric(const string[])
{
	for (new i = 0, j = strlen(string); i < j; i++)
{
		if (string[i] > '9' || string[i] < '0') return 0;
	}
	return 1;
}

stock GetDistanceToPoint(playerid, Float:x2, Float:y2, Float:z2)
{
	new Float:x1, Float:y1, Float:z1, Float:tmpdis;
	GetPlayerPos(playerid,x1,y1,z1);
	tmpdis = floatsqroot(floatpower(floatsub(x2,x1),2)+floatpower(floatsub(y2,y1),2)+floatpower(floatsub(z2,z1),2));
	return floatround(tmpdis);
}

stock GetDistanceBetweenPlayers(playerid, playerid2)
{
	new Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2;
	new Float:tmpdis;
	GetPlayerPos(playerid,x1,y1,z1);
	GetPlayerPos(playerid2,x2,y2,z2);
	tmpdis = floatsqroot(floatpower(floatsub(x2,x1),2)+floatpower(floatsub(y2,y1),2)+floatpower(floatsub(z2,z1),2));
	return floatround(tmpdis);
}

public Float:GetDistanceBetweenPlayers(playerid, targetid)
{
	new Float:x1,Float:y1,Float:z1, Float:x2,Float:y2,Float:z2;
	if(!IsPlayerConnected(playerid) || !IsPlayerConnected(targetid)) return -1.00;
	GetPlayerPos(playerid,x1,y1,z1);
	GetPlayerPos(targetid,x2,y2,z2);
	return floatsqroot(floatpower(floatsub(x2,x1),2)+floatpower(floatsub(y2,y1),2)+floatpower(floatsub(z2,z1),2));
	return fDistance;
}