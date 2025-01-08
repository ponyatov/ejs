# JS Variable reference format {#jvar}

- @ref var
- @ref JsVarRef

  Number of JS Variables allowed and @ref jvar
 
 There are (on 32 bit platforms):
 * 4 bytes of data at the start
 * 4 JsVarRef + 1 JsVarRefCounter
 * 2 bytes of flags at the end
 
 See comments after JsVar in jsvar.c for more info.
 
- `JsVarRef = uint8_t -> 12 bytes/JsVar`       
    - so `JSVAR_CACHE_SIZE = (RAM - 3000) / 12`
- `JsVarRef = uint16_t -> 13->16 bytes/JsVar`  
    - so `JSVAR_CACHE_SIZE = (RAM - 3000) / 16`
- `JsVarRef = uint32_t -> 20 bytes/JsVar`      
    - so `JSVAR_CACHE_SIZE = (RAM - 3000) / 20`
 
NOTE: @ref JSVAR_CACHE_SIZE must be at least 2 less than the number we can fit
        in @ref JsVarRef See `jshardware.c` FLASH constants - all this must be
        able to fit in flash

 We have a few different types:

-   OBJECT/ARRAY - uses @ref firstChild / @ref lastChild to link to NAMEs.
-   BUILT-IN OBJECT - as above, but we use @ref arData to store the name as well.
    This means built in object names must be LESS THAN 8 CHARACTERS
-   FUNCTION - uses @ref firstChild / @ref lastChild to link to NAMEs, and
    callback is used
-   NAME - use @ref nextSibling / @ref  prevSibling linking to other NAMEs, and
    @ref firstChild to link to a Variable of some kind
-   STRING - use @ref firstChild to link to other STRINGs if String value is too
    long
-   INT/DOUBLE - @ref firstChild never used

For 'normal' JsVars used on Espruino Board (@ref LINUX are different to allow
more storage and 64 bit pointers):

Both INT and STRING can also be names:

The size of vars depends on how many variables we need to reference. The bits
for references are packed into a @ref JsVarDataRef structure.

`sizeof(JsVar)` is between 10 and 16bytes depending on @ref JSVARREF_BITS. As an
example, for a 16 byte @ref JsVar:

```
 | Offset | Size | Name    | STRING | STR_EXT  | NAME_STR | NAME_INT | INT  | DOUBLE  | OBJ/FUNC/ARRAY | ARRAYBUFFER | NATIVE_STR | FLAT_STR |
 | 16b    |      |         |        |          |          |          |      |         |                |             | FLASH_STR  |          |
 |--------|------|---------|--------|----------|----------|----------|------|---------|----------------|-------------|------------|----------|
 | 0 - 3  | 4    | varData | data   | data     |  data    | data     | data | data    | nativePtr      | size        | ptr        | charLen  |
 | 4 - 5  | ?    | next    | data   | data     |  next    | next     |  -   | data    | argTypes       | format      | len        | -        |
 | 6 - 7  | ?    | prev    | data   | data     |  prev    | prev     |  -   | data    | argTypes       | format      | ..len      | -        |
 | 8 - 9  | ?    | first   | data   | data     |  child   | child    |  -   | data?   | first          | stringPtr   | ..len      | -        |
 | 10-11  | ?    | refs    | refs   | data     |  refs    | refs     | refs | refs    | refs           | refs        | refs       | refs     |
 | 12-13  | ?    | last    | nextPtr| nextPtr  |  nextPtr |  -       |  -   |  -      | last           | -           | -          | -        |
 | 14-15  | 2    | Flags   | Flags  | Flags    |  Flags   | Flags    | Flags| Flags   | Flags          | Flags       | Flags      | Flags    |

 * NAME_INT_INT/NAME_INT_BOOL are the same as NAME_INT, except 'child' contains the value rather than a pointer
 * NAME_STRING_INT is the same as NAME_STRING, except 'child' contains the value rather than a pointer
 * FLAT_STRING uses the variable blocks that follow it as flat storage for all the data
 * NATIVE_FUNCTION's nativePtr is a pointer to code if there is no child called JSPARSE_FUNCTION_CODE_NAME, but if there is one, it's an index into that child
```
 * For Objects that represent hardware devices, 'nativePtr' is actually set to a special string that
 * contains the device number. See jsiGetDeviceFromClass/jspNewObject
