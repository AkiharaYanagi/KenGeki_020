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
#include "../../GameMain/GameConst.h"
#include "../../GameMain/Param.h"
#include "../FtgConst.h"	


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class BG : public TASK_VEC
	{
		//種類
		STAGE_NAME		m_stage_name { STAGE_YUUHINO_HARA };
		
		//背景
		P_Grp			m_bg_C;
		P_Grp			m_bg_L;
		P_Grp			m_bg_R;

		//test カベ表示 背景
		P_Grp			m_wall_L;
		P_Grp			m_wall_R;

		//［デバッグ用］入力説明
		P_Grp			m_input;

		//手前部分表示
		P_GrpEf			m_front;

#if 0
		P_GrpAcv		m_bg_back;
		P_GrpAcv		m_bg_middle;
		P_GrpAcv		m_bg_front;

		P_PrmRect		m_bg_white;

		//サブ背景位置差分
		float			m_subWall_dx { - GAME_WIDTH };

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


		void ParamInit ( P_Param pParam );
		void Load ();
		void Init ();
		void Move ();

		//ステージ名設定
		void SetStageName ( STAGE_NAME name )
		{
			m_stage_name = name;
		}

		//共通グラフィック処理
		void Grp ();

#if 0
		//暗転
		void SetBlackOut ( bool b );
		void OnBlackOut ();
		void OffBlackOut ();

		//条件確認
		bool IsBlackOut () const { return m_tmrBlackOut->IsActive (); }

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

		void LoadFrontOb ();
	};

	using P_BG = std::shared_ptr < BG >;


}	//namespace GAME


