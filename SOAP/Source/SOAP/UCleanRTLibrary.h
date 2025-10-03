#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/Texture2D.h"
#include "UCleanRTLibrary.generated.h"

UCLASS()
class SOAP_API UCleanRTLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="CleanRT")
    static bool ReadRTAndCount(UTextureRenderTarget2D* RT, UTexture2D* Mask, float Threshold,
                               UPARAM(ref) int32& OutClean, UPARAM(ref) int32& OutValid);
};
