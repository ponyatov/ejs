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
