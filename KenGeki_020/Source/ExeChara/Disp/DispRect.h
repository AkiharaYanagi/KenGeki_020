//=================================================================================================
//
// DispRect ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../Rect/CharaRect.h"
//#include "../../FtgMain/G_Ftg.h"
//#include "../../GameMain/GameConst.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
#if 0
	using VP_PrmRect = std::vector < P_PrmRect >;
	using PVP_PrmRect = std::shared_ptr < VP_PrmRect >;
#endif // 0

	using AP_PrmRect = s3d::Array < P_PrmRect >;


	class DispRect : public TASK_VEC
	{
		//参照するキャラ実効枠
		P_CharaRect		mp_CharaRect;

		//表示枠
		AP_PrmRect		map_GrpCRect;
		AP_PrmRect		map_GrpARect;
		AP_PrmRect		map_GrpHRect;
		AP_PrmRect		map_GrpORect;

	public:
		DispRect ();
		DispRect ( const DispRect & rhs ) = delete;
		~DispRect ();

		//実効枠設定
		void SetCharaRect ( P_CharaRect pCharaRect );
	
		//表示枠の初期化
		void InitRect ();

		//更新
		void Update ();

		//------------------
		//表示状態に変更
		void OnRect ();

		//非表示状態に変更
		void OffRect ();

		//-------------------

		//表示枠設定
		void SetGrpRect ( AP_PrmRect& apGrpRect, PV_RECT pvRect );
		void SetCRect ( PV_RECT pvRect ) { SetGrpRect ( map_GrpCRect, pvRect ); }
		void SetARect ( PV_RECT pvRect ) { SetGrpRect ( map_GrpARect, pvRect ); }
		void SetHRect ( PV_RECT pvRect ) { SetGrpRect ( map_GrpHRect, pvRect ); }
		void SetORect ( PV_RECT pvRect ) { SetGrpRect ( map_GrpORect, pvRect ); }

	private:
		//初期化用
		P_PrmRect Make ( DWORD clr );
	};

	using P_DispRect = std::shared_ptr < DispRect >;


}	//namespace GAME


