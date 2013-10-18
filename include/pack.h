#ifndef PACK_H_
#define PACK_H_

// packing attribute of structs - VC++ and gcc
#ifdef WIN32
	#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#else
	#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

#endif