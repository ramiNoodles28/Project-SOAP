#include "UCleanRTLibrary.h"
#include "RenderUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogCleanRT, Log, All);

static bool ReadMaskL8(UTexture2D* Tex, TArray<uint8>& Out, int32& W, int32& H)
{
  if (!Tex || !Tex->GetPlatformData() || Tex->GetPlatformData()->Mips.Num()==0) return false;
  auto& Mip = Tex->GetPlatformData()->Mips[0];
  W = Mip.SizeX; H = Mip.SizeY;
  void* Data = Mip.BulkData.LockReadOnly();
  const int64 Size = Mip.BulkData.GetBulkDataSize();
  Out.SetNumUninitialized(Size);
  FMemory::Memcpy(Out.GetData(), Data, Size);
  Mip.BulkData.Unlock();
  return true;
}

bool UCleanRTLibrary::ReadRTAndCount(UTextureRenderTarget2D* RT, UTexture2D* Mask, float Threshold,
                                     int32& OutClean, int32& OutValid)
{
  OutClean=0; OutValid=0;
  if (!RT || !RT->GameThread_GetRenderTargetResource() || !Mask) return false;

  const int32 W = RT->SizeX, H = RT->SizeY;

  TArray<FLinearColor> RTPixels;
  if (!RT->GameThread_GetRenderTargetResource()->ReadLinearColorPixels(RTPixels)) return false;
  if (RTPixels.Num() != W*H) return false;
  TArray<uint8> MaskL8; int32 MW=0, MH=0;
  if (!ReadMaskL8(Mask, MaskL8, MW, MH)) return false;
  if (MW!=W || MH!=H) return false;

  const float MaskThr = 0.5f * 255.f;
  for (int32 i=0;i<W*H;++i)
  {
    const bool bValid = MaskL8[i] > MaskThr;
    if (!bValid) continue;
    ++OutValid;
    if (RTPixels[i].R > Threshold) ++OutClean;
  }
  return true;
}
