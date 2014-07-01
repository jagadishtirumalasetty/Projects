#undef DEBUG_CONSOLE

#ifdef DEBUG
	#ifdef DEBUG_CONSOLE
		#define debug(var) fprintf(stderr,__FILE__ ":%d" #var " = %d\n",__LINE__, var)
	#else
		#define debug(format,var) messagef( "DEBUG", __FILE__ ":" format "\n" #var " = %d\n", __LINE__, (int)var)
	#endif
#else
#define debug(var) 
#endif