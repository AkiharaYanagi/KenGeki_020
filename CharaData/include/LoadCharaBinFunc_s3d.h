//=================================================================================================
//
// LoadCharaBinFunc_s3d ヘッダファイル
//
//=================================================================================================
#pragma once
//#include "Game.h"
#include "Chara.h"
#include "LoadCharaBinUtl_s3d.h"
#include "DebugOutTrace.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------------------
	//	LoadCharaBinで用いる関数群
	//------------------------------------------------------------
	class LoadCharaBinFunc_s3d
	{
		LoadCharaBinUtl_s3d		m_utl;

	public:
		LoadCharaBinFunc_s3d ();
		LoadCharaBinFunc_s3d ( const LoadCharaBinFunc_s3d & rhs ) = delete;
		~LoadCharaBinFunc_s3d () = default;

		//------------------------------------------------------------
		void LoadChara ( s3d::BinaryReader & br, Chara & ch );
		//------------------------------------------------------------
		void LoadCharaScript ( s3d::BinaryReader & br, Chara & ch );
		void LoadCharaImage ( s3d::BinaryReader & br, Chara & ch );
		//------------------------------------------------------------

		void LoadBehavior ( s3d::BinaryReader & br, Chara & ch );
		void LoadGarnish ( s3d::BinaryReader & br, Chara & ch );

		void LoadCommand ( s3d::BinaryReader & br, Chara & ch );
		void LoadBranch ( s3d::BinaryReader & br, Chara & ch );
		void LoadRoute ( s3d::BinaryReader & br, Chara & ch );

		void LoadScript ( s3d::BinaryReader & br, Script & scp );
		void LoadScpPrm_Btl ( s3d::BinaryReader & br, Script & scp );
		void LoadScpPrm_Stg ( s3d::BinaryReader & br, Script & scp );


		//------------------------------------------------------------
//		void LoadImg ( P_Byte buf, UINT & pos, PAP_Tx pvp_tx );
		void LoadImg ( s3d::BinaryReader & br, PAP_Tx pap_tx );
	};


}	//namespace GAME


