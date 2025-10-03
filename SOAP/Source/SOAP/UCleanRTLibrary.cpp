#include "UCleanRTLibrary.h"
#include "RenderUtils.h"

static bool ReadMaskL8(UTexture2D* Tex, TArray<uint8>& Out, int32& W, int32& H)
{
    if (!Tex || !Tex->GetPlatformData() || Tex->GetPlatformData()->Mips.Num() == 0)
        return false;

    FTexturePlatformData* PD = Tex->GetPlatformData();
    FTexture2DMipMap& Mip = PD->Mips[0];

    W = Mip.SizeX; H = Mip.SizeY;

    const void* Data = Mip.BulkData.LockReadOnly();
    const int64 Size64 = Mip.BulkData.GetBulkDataSize();
    if (Size64 <= 0) { Mip.BulkData.Unlock(); return false; }

    const int32 Size = static_cast<int32>(Size64);
    Out.SetNumUninitialized(Size);
    FMemory::Memcpy(Out.GetData(), Data, Size);
    Mip.BulkData.Unlock();
    return true;
}

bool UCleanRTLibrary::ReadRTAndCount(UTextureRenderTarget2D* RT, UTexture2D* Mask, float Threshold,
    int32& OutClean, int32& OutValid)
{
    if (RTPixels.Num() == 0 || W <= 0 || H <= 0)
    {
        return false;
    }
    OutClean = 0; OutValid = 0;
    if (!RT || !Mask) return false;

    FTextureRenderTargetResource* RTRes = RT->GameThread_GetRenderTargetResource();
    if (!RTRes) return false;

    const int32 W = RT->SizeX, H = RT->SizeY;

    TArray<FLinearColor> RTPixels;
    if (!RTRes->ReadLinearColorPixels(RTPixels) || RTPixels.Num() != W * H)
        return false;

    TArray<uint8> MaskL8; int32 MW = 0, MH = 0;
    if (!ReadMaskL8(Mask, MaskL8, MW, MH) || MW != W || MH != H)
        return false;

    const uint8 MaskThr = 128;
    for (int32 i = 0; i < W * H; ++i)
    {
        if (MaskL8[i] <= MaskThr) continue;
        ++OutValid;
        if (RTPixels[i].R > Threshold) ++OutClean;
    }
    return true;
}
