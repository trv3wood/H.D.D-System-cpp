#include "code.h"

const std::string HDD_CODE = R"(
// CopyRight (C) A.K.A Hollow Deep Dive System
// Led by Helios Research Institute
// Author: BW
// deep_dive_prototype_v4.h
//////////////////////////////////////////////
#ifndef DEEP_DIVE_PROTOTYPE_V4_H
#define DEEP_DIVE_PROTOTYPE_V4_H
#include <MAP>
#include "helios_signal.h"
namespace Hollow
{
  class DeepDivePrototypeV4 : public DeepDiveBase
  {
    private:
      HELIOS::BangbooHandle m_handle;
      HChessboardMap<EHDomainType.EHSensorType> m_crossDomainSensorMap;
      HSensorContainer<VisualSensor> m_visualSensorContainer;

    public:
      virtual void RegisterBangbooHandle(HollowSignal signal) override;
      HCRESULT SyncVisualSensor(const HMatrics matWorld, HLINT hollowIndex);
  };
}
#endif // DEEP_DIVE_PROTOTYPE_V4_H

// CopyRight (C) A.K.A Hollow Deep Dive System
// Led by Helios Research Institute
// Author: BW
// deep_dive_prototype_v4.cpp
//////////////////////////////////////////////
#include "deep_dive_prototype_v4.h"
#include "hollow_toolkit.h"
#include "hollow_boost.h"
namespace Hollow
{
  void DeepDivePrototypeV4::RegisterBangbooHandle(HollowSignal signal)
  {
    if (m_initState != HollowInitState::HIS_SUCCESS)
      return;

    EHBoostType boostType = signal->GetBoostType();
    switch (boostType)
    {
      case EHBoostType.DEFAULT:
        m_handle = HELIOS::BangbooHandle.DEFAULT;
        break;
      default:
        break;
    }
  }
}



System boot complete.)";
