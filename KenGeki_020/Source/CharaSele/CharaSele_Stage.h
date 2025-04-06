//=================================================================================================
//
//	CharaSele_Stage
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/GameConst.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class CharaSele_Stage	: public TASK_VEC
	{
		//画像
		P_Grp			m_stageSelect;			//プレビュー
		P_GrpBlink		m_stageSelectTri;		//矢印
		P_GrpBlink		m_txt_StageSelect;		//文字表示

		//スクロール
		P_Grp			m_scroll_Stage;
		float			m_scrlStg_x { 0 };

	public:
		CharaSele_Stage ();
		CharaSele_Stage ( const CharaSele_Stage & rhs ) = delete;
		~CharaSele_Stage ();

		void Move ();

		void On ();
		void Off ();

		void Prev ();
		void Next ();
		void Decide ();

		void SetStage ( STAGE_NAME name );
		STAGE_NAME GetStageName () const { return (STAGE_NAME)m_stageSelect->GetIndexTexture(); }

	private:
		static const float STG_BG_X;
		static const float STG_BG_Y;
		static const float STG_X;
		static const float STG_Y;
		static const float STG_TRI_X;
		static const float STG_TRI_Y;
		static const float TXT_STSL_X;
		static const float TXT_STSL_Y;

	};

	using P_CharaSele_Stage = std::shared_ptr < CharaSele_Stage >;


}	//namespace GAME

