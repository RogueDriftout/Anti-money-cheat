/* 
Advanced anti cash cheat by RogueDrifter 2018/2/9
USAGE: Include in all scripts and use the following:
-=-=-=-=-=-=-=-=-=-=
Callback:
-=-=-=-=-=
OnPlayerCashCheat(playerid, oldcash, newcash, amount);
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
Whereas:
-=-=-=-=
playerid = the player who used cheats to spoof cash.
oldcash = the original cash he had before using cheats.
newcash = the current amount of cash after he used cheats.
amount = the amount of cash he used cheats to spoof.
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

#if defined _rAntiCashCheat_
	#endinput
#endif

#define _rAntiCashCheat_

#include <a_samp>

#if !defined FILTERSCRIPT 

enum E_AMC_INFO
{
	bool:AmcCashImmu,
	
	AmcPTimer,

	AmcCash

};

new 
	rAmc_Player[MAX_PLAYERS][E_AMC_INFO];

#if defined Amc_OnPlayerDisconnect
	forward Amc_OnPlayerDisconnect(playerid, reason);
#endif

#if defined Amc_OnPlayerConnect
	forward Amc_OnPlayerConnect(playerid);
#endif

forward Amc_GivePlayerMoney(playerid, amount);
forward Amc_ResetPlayerMoney(playerid);
forward Amc_GetPlayerMoney(playerid);

forward Amc_ResetImmunity(playerid);
forward Amc_CheckCash(playerid);

public Amc_ResetImmunity(playerid) return rAmc_Player[playerid][AmcCashImmu]= false;
public Amc_GetPlayerMoney(playerid) return rAmc_Player[playerid][AmcCash];

public Amc_CheckCash(playerid)
{
	new rAmcTempCash;
    rAmcTempCash = GetPlayerMoney(playerid);

    if(rAmc_Player[playerid][AmcCash] < rAmcTempCash && !rAmc_Player[playerid][AmcCashImmu])
    {
        new rAmcSumUp = rAmcTempCash - rAmc_Player[playerid][AmcCash];

        	#if defined OnPlayerCashCheat
        OnPlayerCashCheat(playerid, rAmc_Player[playerid][AmcCash], rAmcTempCash, rAmcSumUp);
        #endif

        GivePlayerMoney(playerid, - rAmcSumUp);
        }

	return 1;
}

public Amc_ResetPlayerMoney(playerid)
{
	if(!rAmc_Player[playerid][AmcCashImmu]) SetTimerEx("Amc_ResetImmunity", 3000, false, "i", playerid);
	rAmc_Player[playerid][AmcCashImmu]= true;

	rAmc_Player[playerid][AmcCash] = 0;
	ResetPlayerMoney(playerid);
	return 1;
}

public Amc_GivePlayerMoney(playerid, amount)
{
	if(!rAmc_Player[playerid][AmcCashImmu]) SetTimerEx("Amc_ResetImmunity", 3000, false, "i", playerid);
	rAmc_Player[playerid][AmcCashImmu]= true;

	rAmc_Player[playerid][AmcCash] += amount;
	GivePlayerMoney(playerid, amount);
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	rAmc_Player[playerid][AmcCashImmu]= false;
	KillTimer(rAmc_Player[playerid][AmcPTimer]);
		#if defined Amc_OnPlayerDisconnect
	return Amc_OnPlayerDisconnect(playerid, reason);
		#else
	return 1;
		#endif
}

public OnPlayerConnect(playerid)
{
	Amc_ResetPlayerMoney(playerid);
	rAmc_Player[playerid][AmcPTimer] = SetTimerEx("Amc_CheckCash", 15000, true, "i", playerid);

		#if defined Amc_OnPlayerConnect
	return Amc_OnPlayerConnect(playerid);
		#else
	return 1;
		#endif
}

#if defined OnPlayerCashCheat
	forward OnPlayerCashCheat(playerid, oldcash, newcash, amount);
#endif

#if defined _ALS_OnPlayerDisconnect
  #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect Amc_OnPlayerDisconnect

#if defined _ALS_OnPlayerConnect
  #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect Amc_OnPlayerConnect

#if defined _ALS_GivePlayerMoney
  #undef GivePlayerMoney
#else
    #define _ALS_GivePlayerMoney
#endif

#define GivePlayerMoney Amc_GivePlayerMoney

#if defined _ALS_ResetPlayerMoney
  #undef ResetPlayerMoney
#else
    #define _ALS_ResetPlayerMoney
#endif

#define ResetPlayerMoney Amc_ResetPlayerMoney

#if defined _ALS_GetPlayerMoney
  #undef GetPlayerMoney
#else
    #define _ALS_GetPlayerMoney
#endif

#define GetPlayerMoney Amc_GetPlayerMoney

#else

stock Amc_FGetPlayerMoney(playerid)
	return CallRemoteFunction("Amc_GetPlayerMoney","i",playerid);

stock Amc_FGivePlayerMoney(playerid, money)
	return CallRemoteFunction("Amc_GivePlayerMoney","ii",playerid, money);

stock Amc_FResetPlayerMoney(playerid)
	return CallRemoteFunction("Amc_ResetPlayerMoney","i",playerid);

#if defined _ALS_GivePlayerMoney
  #undef GivePlayerMoney
#else
    #define _ALS_GivePlayerMoney
#endif

#define GivePlayerMoney Amc_FGivePlayerMoney

#if defined _ALS_ResetPlayerMoney
  #undef ResetPlayerMoney
#else
    #define _ALS_ResetPlayerMoney
#endif

#define ResetPlayerMoney Amc_FResetPlayerMoney

#if defined _ALS_GetPlayerMoney
  #undef GetPlayerMoney
#else
    #define _ALS_GetPlayerMoney
#endif

#define GetPlayerMoney Amc_FGetPlayerMoney

#endif
