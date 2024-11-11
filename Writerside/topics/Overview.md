# Overview

## Prerequisites

To get started with the plugin, you need to have already set-up unreal engines gameplay debugger extension.

If you're unsure on how to do that, you can view a **[simplified example here](GameplayDebuggerPlugin.md)**

## Register a new gameplay debugger category in your editor module

```C++
void FEditorExtensionsGameEditorModule::StartupModule() {
#if WITH_GAMEPLAY_DEBUGGER
	IGameplayDebugger& GameplayDebuggerModule = IGameplayDebugger::Get();

	GameplayDebuggerModule.RegisterCategory(
		/*Category name*/"Example",
		/*Create instance delegate*/IGameplayDebugger::FOnGetCategory::CreateLambda([this]() -> TSharedRef<FGameplayDebuggerCategory> {
			return MakeShared<FGameplayDebuggerCategoryExample>();
		}),
		/*Enabled modes*/EGameplayDebuggerCategoryState::EnabledInGameAndSimulate
	);

	GameplayDebuggerModule.NotifyCategoriesChanged();
#endif
}

void FEditorExtensionsGameEditorModule::ShutdownModule() {
#if WITH_GAMEPLAY_DEBUGGER
	if (IGameplayDebugger::IsAvailable()) {
		IGameplayDebugger& GameplayDebuggerModule = IGameplayDebugger::Get();
		GameplayDebuggerModule.UnregisterCategory("Example");
		GameplayDebuggerModule.NotifyCategoriesChanged();
	}
#endif
}

```

## Create a new gameplay debugger category

**It's important that your class inherits from `FGameplayDebuggerCategoryExtended`**

### GameplayDebuggerExample.h
```C++
class FGameplayDebuggerCategoryExample : public FGameplayDebuggerCategoryExtended
{
public:
    // These are some settings, which we can toggle by keybinds, and will be saved
	bool bDrawNodeOverheads = true;
	bool bDrawSecondCategory = true;

	FGameplayDebuggerCategoryExample();

	virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;
	virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;
};
```

### GameplayDebuggerExample.cpp
```C++
#include "GameplayDebuggerExample.h"
#include "GameplayDebuggerSetting.h"
#include "Overheads/Overhead.h"

FGameplayDebuggerCategoryExample::FGameplayDebuggerCategoryExample() {
	bShowOnlyWithDebugActor   = false;
	bAllowLocalDataCollection = false;

	// Just an example of the saved bindings
    // Z will toggle the bDrawNodeOverheads
	AddSavedBind("DrawOverheads")
		.Bind(EKeys::Z.GetFName(), FGameplayDebuggerInputModifier::None)
		.SyncTo(&bDrawNodeOverheads);

    // X will toggle the bDrawSecondCategory
	AddSavedBind("Draw Second Category")
		.Bind(EKeys::X.GetFName(), FGameplayDebuggerInputModifier::None)
		.SyncTo(&bDrawSecondCategory);

}

void FGameplayDebuggerCategoryExample::CollectData(APlayerController* OwnerPC, AActor* DebugActor) {
	FGameplayDebuggerCategoryExtended::CollectData(OwnerPC, DebugActor);

	if (bDrawNodeOverheads) {
		// This could be some actor position in the world...
		auto& Overhead = Collector.Add(FVector::Zero());
		Overhead.Add("Primary key", "Value");

		Overhead.Separator();

		auto& Category = Overhead.Category("Category Example");
		Category.Add("Key", "Value");

		{
			FOverheadCategoryIndentScope Indent(Category);
			Category.Add("Indented Key", "Value");
		}
	}

	if (bDrawSecondCategory) {
		auto& AnotherOverhead = Collector.Add(FVector::Zero(), false);
		auto& AnotherCategory = AnotherOverhead.Category("Another Category");
		AnotherCategory.Add("Key", "Value");
		{
			FOverheadCategoryIndentScope Indent(AnotherCategory);
			AnotherCategory.Add("Indented Key", "Value");
		}
	}

}

void FGameplayDebuggerCategoryExample::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) {
	FGameplayDebuggerCategoryExtended::DrawData(OwnerPC, CanvasContext);

	// Bindings & Overheads are drawn by the base class(FGameplayDebuggerCategoryExtended)

}
```