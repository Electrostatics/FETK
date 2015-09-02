// Maloc defines
#if defined(__cplusplus)
/** @brief Setup so this include file (and subsequent) will work for both C and C++ */
#   define VCXX
/** @brief Setup so this include file (and subsequent) will work for both C and C++ */
#   define VEXTERNC extern "C"
#else
/** @brief Setup so this include file (and subsequent) will work for both C and C++ */
#   define VCC
/** @brief Setup so this include file (and subsequent) will work for both C and C++ */
#   define VEXTERNC extern
#endif

/*
 * ***************************************************************************
 * Private and Public type modifier simulation
 * ***************************************************************************
 */

#define VPRIVATE static      /**< @brief Mimic C++ "Private" type modifier */
#define VPUBLIC  /*empty*/   /**< @brief Mimic C++ "Public" type modifier  */

