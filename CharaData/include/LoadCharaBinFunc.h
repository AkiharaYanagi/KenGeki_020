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

		void LoadChara ( CUPR_BYTE buf, UINT & pos, Chara & ch );
		void LoadCharaScript ( CUPR_BYTE buf, UINT & pos, Chara & ch );
		void LoadCharaImage ( CUPR_BYTE buf, UINT & pos, Chara & ch );

		void LoadBehavior ( CUPR_BYTE buf, UINT & pos, Chara & ch );
		void LoadGarnish ( CUPR_BYTE buf, UINT & pos, Chara & ch );

		void LoadCommand ( CUPR_BYTE buf, UINT & pos, Chara & ch );
		void LoadBranch ( CUPR_BYTE buf, UINT & pos, Chara & ch );
		void LoadRoute ( CUPR_BYTE buf, UINT & pos, Chara & ch );

		void LoadScript ( CUPR_BYTE buf, UINT & pos, Script & scp );
		void LoadScpPrm_Btl ( CUPR_BYTE buf, UINT & pos, Script & scp );
		void LoadScpPrm_Stg ( CUPR_BYTE buf, UINT & pos, Script & scp );

		void LoadImg ( CUPR_BYTE buf, UINT & pos, PAP_Tx pvp_tx );
	};


}	//namespace GAME


