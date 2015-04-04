/* check for required command macro */
#ifndef HOST
  #error -DHOST="hostname"
#endif

#ifndef SCHEMA
  #error -DSCHEMA="schema"
#endif

#ifndef USER
  #error -DUSER="user"
#endif

#ifndef PASSWORD
  #error -DPASSWORD="password"
#endif

/* tricks to make -Dmacro string value,
   declare sequence #DOES# matter!!! */
#define DECLARE_STRING(x)   TO_STRING(x)
#define TO_STRING(x)        #x
