/*
 ============================================================================
 Name        : iptest.c
 Author      : abp
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int UINT;
typedef unsigned char UCHAR;

#define IPSYMBOLS "0123456789."
#define NETSYMBOLS "0123456789./"

UINT checkip (char *tstip) {
	UCHAR endofstring;												// last symbol in the string must be \0x
	char *ip = tstip;
	UINT octet0, octet1, octet2, octet3;							// for ip address octets

	if (strspn(ip, IPSYMBOLS) < strlen(ip)) return 0;			// check for valid symbols
	if (sscanf(ip, "%3u.%3u.%3u.%3u%c", 							// fill octets, check for valid format
			&octet0, &octet1, &octet2, &octet3, &endofstring) != 4) return 0;
	if ((octet0 | octet1 | octet2 | octet3) > 255) return 0;		//check for
	return 1;
}

UINT checknet (char *tstip) {
	UCHAR endofstring;												// last symbol in the string must be \0x
	char *ip = tstip;
	UINT octet0, octet1, octet2, octet3, mask;
	if (strspn(ip, NETSYMBOLS) < strlen(ip)) return 0;			// check for valid symbols
	if (sscanf(ip, "%3u.%3u.%3u.%3u/%2u%c", 						// fill octets, check for valid format
			&octet0, &octet1, &octet2, &octet3, &mask, &endofstring) != 5) return 0;
	if (((octet0 | octet1 | octet2 | octet3) > 255) || mask > 32) return 0;		//check for
	return 1;
}

int main(int argc, char** argv) {
	UINT i;

	if (argc < 2) {
		printf ("Usage:\n iptest inet_addr0 inet_addr1 inet_addr2 ...\n");
		return EXIT_FAILURE;
	}

	for (i=1; i<argc; i++){
		if (checkip(argv[i])) printf("%s = ip\n", argv[i]);
		else if (checknet(argv[i])) printf("%s = net\n", argv[i]);
		else printf ("%s = err\n", argv[i]);
	}
	return EXIT_SUCCESS;
}
