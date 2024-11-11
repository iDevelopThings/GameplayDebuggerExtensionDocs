# Saved Binds Reference

## Creating a bind

```C++
AddSavedBind(FName SettingName)
```
Adds a new saved bind which will be saved to an .ini file.
```C++
AddDeveloperSettingsBind(UDeveloperSettings* DevSettings, FName SettingName)
```
This will use reflection to bind to an instance of your specified UDeveloperSettings object.

**Both of these methods return a `FGameplayDebuggerSetting` object which allows extra configuration.**

### Bind a key:
```C++
FGameplayDebuggerSetting& Bind(FName InKeyName, FGameplayDebuggerInputModifier InModifier, EGameplayDebuggerInputMode InInputMode);
```
**Example:**
```C++
AddSavedBind("DrawOverheads")
    .Bind(EKeys::Z.GetFName(), FGameplayDebuggerInputModifier::None)
```


### Sync to a variable pointer:
```C++
FGameplayDebuggerSetting& SyncTo(bool* InPropertyPtr)
```
Example:
```C++
// Header file has `bool bMySetting = true;`
AddSavedBind("MySetting")
    .SyncTo(&bMySetting);
```


### Set a title
```C++
FGameplayDebuggerSetting& Title(FString InTitle)
```
