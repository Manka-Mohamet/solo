/*
 Module kan waxa uu ka koobanyahay sidda aynu
u keedinayno constant values like: numbers, boolean, string etc.

waxay isticmaaleynaa 8 macros si aan  sola value ugu badalno c struct.
*/

#ifndef sola_value_h
#define sola_value_h

#include "common.h"

/*
  @Discription - enum kani waxa uu ka koobanyahay different dataTypes
	ay sola language ay isticmaaleyso.
	haddii aad rabto inaad kusoo darti new dataType, enum kan waa inaad dhaxgalisaa .
 @NUMBER - type kani waxa uu handle gareenayaa all numeric types like: int, double.
 @BOOL  _  type kani  waa boolean waxa uu handle gareenayaa: true, false.
 @NILL  - type kani waa NULL DataType.
 @OBJ   - type kani waa all heap allocated values like: string, functions, class instances.
*/
typedef enum{
	NUMBER,
	BOOL,
	NILL,
	OBJ,

}ValueType;



/*
 @Description -  constant values sidda numbers, string waxaa keydinaayaa Value struct
   Value struct is union  taaso lamicna tahay in c language
   ay noo ogolaaneyso inaa (Memory reusing) sameeno.

 @type -  waa valuega aynu store gareeneyno type kiisa.
 @number - waa meesha aynu ku store gareeneyno number values like: int , double.
 @boolean - waa meesha aynu ku store gareeneyno boolean values like: true, false.
*/
typedef struct{

	ValueType type;
	union{
	      double number;
	      bool boolean;
	}as;

}Value;

/*
 THESE MACROS - wxay numbers, booleans and null ku keydinaayaan 'Value Struct'
*/
#define NUMBER_VAL(value)   ((Value){NUMBER, {.number value}})
#define NIL_VAL             ((Value){NILL, {.number = 0}})
#define BOOL_VAL(value)     ((Value){BOOL,  {.boolean = value}})


/*
THESE MACROS - waxay qaadanaayaan 'Value Struct', kadib waxay soo return gareenayaan literal value.
*/
#define AS_BOOL(value)   ((value).as.boolean)
#define AS_NUMBER(value) ((value).as.number)


/*
THESE MACROS - waxay hubinaayaan 'Value Struct' loosoo baasay inuu type kiisa mid saxanyahay.
*/
#define IS_BOOL(value)    ((value).type == BOOL)
#define IS_NIL(value)     ((value).type == NILL)
#define IS_NUMBER(value)  ((value).type == NUMBER)



/*
 @Description - user waliba code kiisa waxaa ku jira 100s of values
	siddaasi darteed, waxaynu sammeenay dynamic array si aynu ugu keydino dhamaan values.
 @length - waxa uu la socdaa inta elements ee lagu keydiyay arrey daan.
 @capacity - waxa uu la socdaa inta buckets ee la allocate gareeyay.
 @values - waa thick pointer kaaso la socda value ugu horeeya memory location.
*/
typedef struct{

	int length;
	int capacity;
	Value* values;

}ValueArray;




// waxay initialize gareenee new ValueArray.
void initValueArray(ValueArray* array);

//waxay ogolaanee inaan array da ku keydino new Value.
void writeValueArray(ValueArray* array,  Value value);

//waxay ogolaanee inaan free gareeno array dan memoryga ay isticmaashay.
void freeValueArray(ValueArray* array);



#endif
