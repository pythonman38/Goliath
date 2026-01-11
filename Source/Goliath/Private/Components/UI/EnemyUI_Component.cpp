// Midnight Madness, Inc.


#include "Components/UI/EnemyUI_Component.h"

#include "Widgets/GoliathWidgetBase.h"


void UEnemyUI_Component::RegisterEnemyDrawnWidget(UGoliathWidgetBase* InWidgetToRegister)
{
	EnemyDrawnWidgets.Add(InWidgetToRegister);
}

void UEnemyUI_Component::RemoveEnemyDrawnWidgetsIfAny()
{
	if (EnemyDrawnWidgets.IsEmpty()) return;
	
	for (auto DrawnWidget : EnemyDrawnWidgets)
	{
		if (DrawnWidget) DrawnWidget->RemoveFromParent();
	}
	EnemyDrawnWidgets.Empty();
}
