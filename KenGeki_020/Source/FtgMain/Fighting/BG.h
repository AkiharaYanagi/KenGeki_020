//=================================================================================================
//
//	BG ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../FtgConst.h"	


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class BG : public TASK_VEC
	{
		//背景
		P_Grp			m_bg_C;
		P_Grp			m_bg_L;
		P_Grp			m_bg_R;

		//test カベ表示 背景
		P_Grp			m_wall_L;
		P_Grp			m_wall_R;

		//［デバッグ用］入力説明
		P_Grp			m_input;

#if 0
		P_GrpAcv		m_bg_back;
		P_GrpAcv		m_bg_middle;
		P_GrpAcv		m_bg_front;

		P_PrmRect		m_bg_black;
		P_PrmRect		m_bg_white;

		//サブ背景位置差分
		float			m_subWall_dx { - GAME_WIDTH };

		//タイマ
		P_Timer			m_tmrBlackOut;		//暗転
		P_Timer			m_tmrWhiteOut;		//白転

		//壁割り
		P_GrpAcv		m_wall_break;
		P_Timer			m_tmrWallBreak;
		UINT			m_indexTexture { 0 };
#endif // 0

	public:
		BG ();
		BG ( const BG & rhs ) = delete;
		~BG ();

		void Init ();
		void Move ();


		//共通グラフィック処理
		void Grp ();

#if 0
		//条件確認
		bool IsBlackOut () const { return m_tmrBlackOut->IsActive (); }

		//暗転
		void SetBlackOut ( UINT n );
		void OffBlackOut ();

		//白転
		void SetWhiteOut ( UINT n );

		//壁割り
		void StartWallBreak_L ();
		void StartWallBreak_R ();
#endif // 0
	private:
		static const float BG_SIZE_W;
		static const float BG_SIZE_H;
		static const float BG_POS_X;
		static const float BG_POS_Y;
	};

	using P_BG = std::shared_ptr < BG >;


}	//namespace GAME


