// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "CanvasItem.h"
#include "Engine/Canvas.h"
#include "GameFramework/GameUserSettings.h"
#include "Slate/SceneViewport.h"
#include "Materials/Material.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CanvasTypes.h"

AMyHUD::AMyHUD()
{
    PrimaryActorTick.bCanEverTick = true;


}

void AMyHUD::BeginPlay()
{
    if (PlayerOwner != nullptr)
    {
        Char = Cast<AMyCharacter>(PlayerOwner->AcknowledgedPawn);

        if (Char != nullptr)
        {
            Char->SetMyHUD(this);

            ULocalPlayer* LocPlayer = Cast<ULocalPlayer>(PlayerOwner->Player);
            if (LocPlayer && LocPlayer->ViewportClient)
            {
                if (FSceneViewport* s_viewport = LocPlayer->ViewportClient->GetGameViewport())
                {
                    if (UGameUserSettings* settings = GEngine->GetGameUserSettings())
                    {
                        FIntPoint resol = settings->GetScreenResolution();
                        s_viewport->SetFixedViewportSize(resol.X, resol.Y);

                        for (auto itr : Materials)
                            MaterialsInstanceDynamic.Add(UMaterialInstanceDynamic::Create(itr, this));
                    }
                }
            }
        }
    }
}

void AMyHUD::DrawHUD()
{
    if (IsCanvasValid_WarnIfNot() && Char != nullptr)
    {
        FCanvasTileItem TileItem
        (
            FVector2D(HealthBorderStartPosX, HealthBorderStartPosY), 
            GWhiteTexture, 
            FVector2D(HealthBorderLength, HealthBorderWidth), 
            FLinearColor(0.f, 0.f, 0.f, 0.4f)
        );

        TileItem.BlendMode = SE_BLEND_Translucent;
        Canvas->DrawItem(TileItem);

        TileItem.Position = FVector2D(HealthStartPosX, HealthStartPosY);

        float dropEffect = Char->GetHealthDropEffect();
        float health = Char->GetHealth();

        if (dropEffect != health)
        {
            TileItem.Size = FVector2D(HealthLength * dropEffect, HealthWidth);
            TileItem.SetColor(FLinearColor(0.4f, 0.f, 0.f, 1.f));
            Canvas->DrawItem(TileItem);
        }
        else
        {
            TileItem.Size.Y = HealthWidth;
        }

        TileItem.Size.X = health * HealthLength;
        TileItem.SetColor(FLinearColor(0.f, 0.4f, 0.f, 1.f));
        Canvas->DrawItem(TileItem);

        if (Char->IsQuestActive())
        {
            float ScreenX = 50.f;

            for (size_t i = 0; i < (FMath::Min(MaterialsInstanceDynamic.Num(), 6)); i++)
            {
                DrawMaterialSimple(MaterialsInstanceDynamic[i], ScreenX, 950, 500, 500, 0.2f);
                ScreenX += 100.f;
            }
        }
    }
//     
//     DrawRect(FLinearColor(0.f, 0.f, 0.f, 0.4f), 47.f, 47.f, 306.f, 26.f);
//     DrawRect(FLinearColor(0.5f, 0.f, 0.f, 1.f), 50.f, 50.f, 250.f, 20);
//     DrawRect(FLinearColor(0.f, 0.4f, 0.f, 1.f), 50.f, 50.f, 200.f, 20);
}

void AMyHUD::ActivateItemInHUD(uint8 itemID)
{
    if (MaterialsInstanceDynamic.IsValidIndex(itemID))
        MaterialsInstanceDynamic[itemID]->SetScalarParameterValue("Active", 2.f);
}
