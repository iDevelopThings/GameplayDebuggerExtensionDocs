#include "EditorExtensionsGameEditor.h"
#include "GameplayDebuggerExample.h"
#if WITH_GAMEPLAY_DEBUGGER
#include "GameplayDebugger.h"
#endif
#define LOCTEXT_NAMESPACE "FEditorExtensionsGameEditorModule"

void FEditorExtensionsGameEditorModule::StartupModule() {

#if WITH_GAMEPLAY_DEBUGGER
	IGameplayDebugger& GameplayDebuggerModule = IGameplayDebugger::Get();

	GameplayDebuggerModule.RegisterCategory(
		"Example",
		IGameplayDebugger::FOnGetCategory::CreateLambda([this]() -> TSharedRef<FGameplayDebuggerCategory> {
			return MakeShared<FGameplayDebuggerCategoryExample>();
		}),
		EGameplayDebuggerCategoryState::EnabledInGameAndSimulate
	);

	GameplayDebuggerModule.NotifyCategoriesChanged();
#endif
}

void FEditorExtensionsGameEditorModule::ShutdownModule() {
#if WITH_GAMEPLAY_DEBUGGER
	if (IGameplayDebugger::IsAvailable()) {
		IGameplayDebugger& GameplayDebuggerModule = IGameplayDebugger::Get();
		GameplayDebuggerModule.UnregisterCategory("Logistics");
		GameplayDebuggerModule.NotifyCategoriesChanged();
	}
#endif
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEditorExtensionsGameEditorModule, EditorExtensionsGameEditor)
