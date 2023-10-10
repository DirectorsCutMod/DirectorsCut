//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: TF2 proxy dummies, so that materials aren't displayed incorrectly.
//
// $NoKeywords: $
//=================================================================================//

#ifndef _DIRECTORSCUT_DUMMYPROXIES_H_
#define _DIRECTORSCUT_DUMMYPROXIES_H_

#include "proxyentity.h"
#include "materialsystem/imaterial.h"
#include "materialsystem/imaterialvar.h"

class CDummyProxy : public IMaterialProxy
{
public:
	virtual bool Init(IMaterial* pMaterial, KeyValues* pKeyValues);
	virtual void OnBind(void*) {};
	virtual void Release() {};
	virtual IMaterial* GetMaterial();
	IMaterial* mat;
};

class CDummyProxyResultFloat : public CDummyProxy
{
public:
	virtual bool Init(IMaterial* pMaterial, KeyValues* pKeyValues);
	IMaterialVar* resultVar;
};

class CDummyProxyResultFloatInverted : public CDummyProxy
{
public:
	virtual bool Init(IMaterial* pMaterial, KeyValues* pKeyValues);
	IMaterialVar* resultVar;
};

class CDummyProxyResultRGB : public CDummyProxy
{
public:
	virtual bool Init(IMaterial* pMaterial, KeyValues* pKeyValues);
	IMaterialVar* resultVar;
};

class CDummyProxyResultRGBInverted : public CDummyProxy
{
public:
	virtual bool Init(IMaterial* pMaterial, KeyValues* pKeyValues);
	IMaterialVar* resultVar;
};

class CDummyInvisProxy : public CDummyProxy {};
class CDummySpyInvisProxy : public CDummyProxy {};
class CDummyWeaponInvisProxy : public CDummyProxy {};
class CDummyVmInvisProxy : public CDummyProxy {};
class CDummyBuildingInvisProxy : public CDummyProxy {};
class CDummyCommunityWeaponProxy : public CDummyProxy {};
class CDummyInvulnLevelProxy : public CDummyProxy {};
class CDummyBurnLevelProxy : public CDummyProxyResultFloat {};
class CDummyYellowLevelProxy : public CDummyProxyResultFloatInverted {};
class CDummyModelGlowColorProxy : public CDummyProxyResultRGB {};
class CDummyItemTintColorProxy : public CDummyProxyResultRGB {};
class CDummyBuildingRescueLevelProxy : public CDummyProxy {};
class CDummyTeamTextureProxy : public CDummyProxy {};
class CDummyAnimatedWeaponSheenProxy : public CDummyProxy {};
class CDummyWeaponSkinProxy : public CDummyProxy {};
class CDummyShieldFalloffProxy : public CDummyProxy {};
class CDummyStatTrakIllumProxy : public CDummyProxy {};
class CDummyStatTrakDigitProxy : public CDummyProxy {};
class CDummyStatTrakIconProxy : public CDummyProxy {};
class CDummyStickybombGlowColorProxy : public CDummyProxy {};
class CDummySniperRifleChargeProxy : public CDummyProxy {};
class CDummyHeartbeatProxy : public CDummyProxy {};
class CDummyWheatlyEyeGlowProxy : public CDummyProxy {};
class CDummyBenefactorLevelProxy : public CDummyProxy {};

EXPOSE_INTERFACE(CDummyInvisProxy, IMaterialProxy, "invis" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummySpyInvisProxy, IMaterialProxy, "spy_invis" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyWeaponInvisProxy, IMaterialProxy, "weapon_invis" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyVmInvisProxy, IMaterialProxy, "vm_invis" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyBuildingInvisProxy, IMaterialProxy, "building_invis" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyCommunityWeaponProxy, IMaterialProxy, "CommunityWeapon" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyInvulnLevelProxy, IMaterialProxy, "InvulnLevel" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyBurnLevelProxy, IMaterialProxy, "BurnLevel" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyYellowLevelProxy, IMaterialProxy, "YellowLevel" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyModelGlowColorProxy, IMaterialProxy, "ModelGlowColor" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyItemTintColorProxy, IMaterialProxy, "ItemTintColor" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyBuildingRescueLevelProxy, IMaterialProxy, "BuildingRescueLevel" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyTeamTextureProxy, IMaterialProxy, "TeamTexture" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyAnimatedWeaponSheenProxy, IMaterialProxy, "AnimatedWeaponSheen" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyWeaponSkinProxy, IMaterialProxy, "WeaponSkin" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyShieldFalloffProxy, IMaterialProxy, "ShieldFalloff" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyStatTrakIllumProxy, IMaterialProxy, "StatTrakIllum" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyStatTrakDigitProxy, IMaterialProxy, "StatTrakDigit" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyStatTrakIconProxy, IMaterialProxy, "StatTrakIcon" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyStickybombGlowColorProxy, IMaterialProxy, "StickybombGlowColor" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummySniperRifleChargeProxy, IMaterialProxy, "SniperRifleCharge" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyHeartbeatProxy, IMaterialProxy, "Heartbeat" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyWheatlyEyeGlowProxy, IMaterialProxy, "WheatlyEyeGlow" IMATERIAL_PROXY_INTERFACE_VERSION);
EXPOSE_INTERFACE(CDummyBenefactorLevelProxy, IMaterialProxy, "BenefactorLevel" IMATERIAL_PROXY_INTERFACE_VERSION);

#endif // _DIRECTORSCUT_DUMMYPROXIES_H_
