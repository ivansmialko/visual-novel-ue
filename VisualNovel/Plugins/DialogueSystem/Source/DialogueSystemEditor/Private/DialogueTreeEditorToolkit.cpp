// Fill out your copyright notice in the Description page of Project Settings.



#include "DialogueTreeEditorToolkit.h"
#include "DialogueTreeGraphNode.h"
#include "DialogueTreeGraphSchema.h"
#include "Widgets/Docking/SDockTab.h"
#include "SDialogueTreeWidget.h"
#include "Modules/ModuleManager.h"
#include "GraphEditor.h"

#include "Kismet2/BlueprintEditorUtils.h"

const FName FDialogueTreeEditorToolkit::GraphCanvasTabId{ TEXT("DialogueTreeEditor_GraphCanvas") };
const FName FDialogueTreeEditorToolkit::PropertiesTabId{ TEXT("DialogueTreeEditor_Properties") };


void FDialogueTreeEditorToolkit::InitEditor(const TArray<UObject*>& InObjects)
{
	DialogueTree = Cast<UDialogueTree>(InObjects[0]);

	if (!DialogueTree->GetGraph())
	{
		DialogueTree->DialogueTreeGraph = CreateGraph();
	}
	CreateInternalWidgets();

	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("DialogueTreeEditorLayout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewSplitter()
				->SetSizeCoefficient(0.6f)
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.8f)
					->AddTab(GraphCanvasTabId, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.2f)
					->AddTab(PropertiesTabId, ETabState::OpenedTab)
				)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.4f)
				->AddTab("OutputLog", ETabState::OpenedTab)
			)
		);


	FAssetEditorToolkit::InitAssetEditor(EToolkitMode::Standalone, {}, "DialogueTreeEditor", Layout, true, true, InObjects);
}

void FDialogueTreeEditorToolkit::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(INVTEXT("Dialogue Tree Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();
	
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(GraphCanvasTabId, FOnSpawnTab::CreateSP(this, &FDialogueTreeEditorToolkit::SpawnTab_GraphCanvas))
		.SetDisplayName(INVTEXT("Dialogue Tree Graph"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "GraphEditor.EventGraph_16x"));

	InTabManager->RegisterTabSpawner(PropertiesTabId, FOnSpawnTab::CreateSP(this, &FDialogueTreeEditorToolkit::SpawnTab_Properties))
		.SetDisplayName(INVTEXT("Details"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"));;
}

void FDialogueTreeEditorToolkit::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner(GraphCanvasTabId);
	InTabManager->UnregisterTabSpawner(PropertiesTabId);
}

TSharedRef<SDockTab> FDialogueTreeEditorToolkit::SpawnTab_GraphCanvas(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == GraphCanvasTabId);

	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.Label(INVTEXT("Dialogue Tree Graph"));

	if (DialogueTreeGraphEditor.IsValid())
	{
		SpawnedTab->SetContent(DialogueTreeGraphEditor.ToSharedRef());
	}

	return SpawnedTab;
}

TSharedRef<SDockTab> FDialogueTreeEditorToolkit::SpawnTab_Properties(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == PropertiesTabId);

	return SNew(SDockTab)
		.Label(INVTEXT("Details"))
		[
			DetailsView.ToSharedRef()
		];
}

void FDialogueTreeEditorToolkit::CreateInternalWidgets()
{
	//Create Graph Editor
	DialogueTreeGraphEditor = CreateGraphEditorWidget();

	//Create Details View
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObjects(TArray<UObject*>{DialogueTree});
}

TSharedRef<SGraphEditor> FDialogueTreeEditorToolkit::CreateGraphEditorWidget()
{
	BindGraphEditorCommands();

	//UEdGraph* Graph = CastChecked<UEdGraph>(FBlueprintEditorUtils::CreateNewGraph(DialogueTree, NAME_None, UEdGraph::StaticClass(), UEdGraphSchema::StaticClass()));

	//FGraphNodeCreator<UDialogueTreeNode> NodeCreator(*Graph);
	//UDialogueTreeNode* GraphNode = NodeCreator.CreateNode(true);
	//GraphNode->CreatePin(EEdGraphPinDirection::EGPD_Input, TEXT("Input"), TEXT("Input"));
	//GraphNode->CreatePin(EEdGraphPinDirection::EGPD_Output, TEXT("Output"), TEXT("Output"));
	//NodeCreator.Finalize();

	//FGraphNodeCreator<UDialogueTreeNode> NodeCreator2(*Graph);
	//UDialogueTreeNode* GraphNode2 = NodeCreator2.CreateNode(true);
	//GraphNode2->CreatePin(EEdGraphPinDirection::EGPD_Input, TEXT("Input"), TEXT("Input"));
	//GraphNode2->CreatePin(EEdGraphPinDirection::EGPD_Output, TEXT("Output"), TEXT("Output"));
	//NodeCreator2.Finalize();

	//Graph->GetSchema()->TryCreateConnection(GraphNode->GetPinAt(1), GraphNode2->GetPinAt(0));

	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = INVTEXT("DIALOGUE TREE");

	SGraphEditor::FGraphEditorEvents InEvents;
	//InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FSoundCueEditor::OnSelectedNodesChanged);
	//InEvents.OnTextCommitted = FOnNodeTextCommitted::CreateSP(this, &FSoundCueEditor::OnNodeTitleCommitted);
	//InEvents.OnNodeDoubleClicked = FSingleNodeEvent::CreateSP(this, &FSoundCueEditor::PlaySingleNode);

	return SNew(SGraphEditor)
		.AdditionalCommands(GraphEditorCommands)
		.IsEditable(true)
		.Appearance(AppearanceInfo)
		.GraphToEdit(DialogueTree->GetGraph())
		.GraphEvents(InEvents)
		.AutoExpandActionMenu(true)
		.ShowGraphStateOverlay(false);
}

void FDialogueTreeEditorToolkit::BindGraphEditorCommands()
{
	if (GraphEditorCommands.IsValid())
		return;

	GraphEditorCommands = MakeShareable(new FUICommandList);
}

UEdGraph* FDialogueTreeEditorToolkit::CreateGraph()
{
	UEdGraph* NewGraph = FBlueprintEditorUtils::CreateNewGraph(DialogueTree, NAME_None, UEdGraph::StaticClass(), UDialogueTreeGraphSchema::StaticClass());
	NewGraph->GetSchema()->CreateDefaultNodesForGraph(*NewGraph);

	return NewGraph;
}
