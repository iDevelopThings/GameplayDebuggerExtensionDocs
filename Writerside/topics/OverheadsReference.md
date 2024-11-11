# Overheads Reference

**`FGameplayDebuggerCategoryExtended`** has an instance of `FGameplayDebuggerOverheadCollector` automatically managed for you, accessible via `Collector` property.



## Adding an overhead
Adds/creates a new overhead tile at the specified world position.
```C++
FGameplayDebuggerOverhead& Add(const FVector& WorldPos, bool Unique = false);
```

An `FGameplayDebuggerOverhead` object allows for managing the "overhead tile", an overhead tile consists of categories, but is also a category itself.

### FGameplayDebuggerOverhead methods:

#### Create a new category
```C++
FOverheadCategory& Category(const FString& InLabel);
```


### FOverheadCategory methods:


#### Add a formatted label & value
```C++
FOverheadCategory& AddF(const FString& InLabel, const FmtType& Fmt, Types... Args)
```

#### Add a label & value
```C++
FOverheadCategory& Add(const FString& InLabel, const FString& Value = "")
```

#### Add a separator
```C++
FOverheadCategory& Separator(const FString& InLabel = "", FLinearColor SeparatorColor = GColorList.DimGrey)
```

#### Indent all subsequent writes
```C++
FOverheadCategory& Indent()
```

#### Unindent all subsequent writes
```C++
FOverheadCategory& Unindent()
```