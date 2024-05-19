//=================================================================================================
//
// LoadCharaBinFunc ヘッダファイル
//
//=================================================================================================
#pragma once
//#include "Game.h"
#include "Chara.h"
#include "LoadCharaBinUtl.h"
#include "DebugOutTrace.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------------------
	//	LoadCharaBinで用いる関数群
	//------------------------------------------------------------
	class LoadCharaBinFunc
	{
		LoadCharaBinUtl		m_utl;

	public:
		LoadCharaBinFunc ();
		LoadCharaBinFunc ( const LoadCharaBinFunc & rhs ) = delete;
		~LoadCharaBinFunc () = default;

		void LoadChara ( UP_BYTE buf, UINT & pos, Chara & ch );
		void LoadCharaScript ( UP_BYTE buf, UINT & pos, Chara & ch );
		void LoadCharaImage ( UP_BYTE buf, UINT & pos, Chara & ch );

		void LoadBehavior ( UP_BYTE buf, UINT & pos, Chara & ch );
		void LoadGarnish ( UP_BYTE buf, UINT & pos, Chara & ch );

		void LoadCommand ( UP_BYTE buf, UINT & pos, Chara & ch );
		void LoadBranch ( UP_BYTE buf, UINT & pos, Chara & ch );
		void LoadRoute ( UP_BYTE buf, UINT & pos, Chara & ch );

		void LoadScript ( UP_BYTE buf, UINT & pos, Script & scp );
		void LoadScpPrm_Btl ( UP_BYTE buf, UINT & pos, Script & scp );
		void LoadScpPrm_Stg ( UP_BYTE buf, UINT & pos, Script & scp );

		void LoadImg ( UP_BYTE buf, UINT & pos, PAP_Tx pvp_tx );

	};


}	//namespace GAME


