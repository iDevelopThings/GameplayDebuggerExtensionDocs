# Gameplay Debugger Setup

## Create an editor only module
In rider, you can easily add a new editor module like so; otherwise refer to the UE Documentation

<p><img src="create-editor-module.png" alt="create-editor-module.png" /></p>
<p><img src="create-editor-module-dialog.png" alt="create-editor-module-dialog.png" /></p>

## Add gameplay debugger dependencies to your Build.cs file

Specifically:
``GameplayDebugger``
and the GameplayDebuggerExtension's dependency: ``GameplayDebuggerExtension``

<compare>
    <code-block lang="c#" src="BuildCS.cs"/>
    <code-block lang="c#" src="BuildCS.cs" include-lines="21,22"/>
</compare>

## Setup your editor module:

### EditorExtensionsGameEditorModule.h
```C++
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FEditorExtensionsGameEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
```

### EditorExtensionsGameEditorModule.cpp
```C++
#include "EditorExtensionsGameEditor.h"
#if WITH_GAMEPLAY_DEBUGGER
#include "GameplayDebugger.h"
#endif
#define LOCTEXT_NAMESPACE "FEditorExtensionsGameEditorModule"

void FEditorExtensionsGameEditorModule::StartupModule() {

#if WITH_GAMEPLAY_DEBUGGER
	IGameplayDebugger& GameplayDebuggerModule = IGameplayDebugger::Get();

    [[[// Continue with the overview to setup the plugin)|Overview.md]]]

	GameplayDebuggerModule.NotifyCategoriesChanged();
#endif
}

void FEditorExtensionsGameEditorModule::ShutdownModule() {
#if WITH_GAMEPLAY_DEBUGGER
	if (IGameplayDebugger::IsAvailable()) {
		IGameplayDebugger& GameplayDebuggerModule = IGameplayDebugger::Get();
		
		GameplayDebuggerModule.NotifyCategoriesChanged();
	}
#endif
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEditorExtensionsGameEditorModule, EditorExtensionsGameEditor)

```

