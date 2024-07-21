//=================================================================================================
//
// DispInput ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../GameMain/GameConst.h"
#include "Chara.h"
#include "../Input/CharaInput.h"
//#include "../../FtgMain/G_Ftg.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class DispInput : public TASK_VEC
	{
		//キー入力表示個数
		static const uint32 NUM_DISP_INPUT;	//表示フレーム個数
		static const int32 BASE_X;			//基準位置
		static const int32 BASE_Y;			//基準位置
		static const int32 CHIP_W;			//1個の幅
		static const int32 CHIP_H;			//1個の高

		P_PrmRect		m_bg;		//背景

#if 0
		P_GrpAcv		m_index;	//見出
#endif // 0

		P_Grp			m_grpKey;		//入力表示
		s3d::Array < P_Ob >		map_Ob;

		int32			m_x { 0 };
		float			m_vel { 1.f };
		uint32			m_timer { 0 };

	public:
		DispInput ();
		DispInput ( const DispInput & rhs ) = delete;
		~DispInput ();

//		void Draw ();

		void LoadPlayer ( PLAYER_ID playerID );

		//入力更新
		void UpdateInput ( P_CharaInput pCharaInput );

		//表示切替
		void On ();
		void Off ();

	private:
		bool GetBoolInput ( P_CharaInput pCharaInput, int n, int i );
	};

	using P_DispInput = std::shared_ptr < DispInput >;


}	//namespace GAME


