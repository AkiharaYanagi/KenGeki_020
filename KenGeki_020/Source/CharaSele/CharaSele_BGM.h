//=================================================================================================
//
//	CharaSele_BGM
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/SoundConst.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//BGMセレクト
	class CharaSele_BGM	: public TASK_VEC
	{
		//選択
		BGM_ID			m_bgm_id { BGM_ID_GABA };

		//画像
		P_Grp			m_bgmSelect;		//名前画像
		P_GrpBlink		m_bgmSelectTri;		//選択矢印
		P_GrpBlink		m_txt_BGMSelect;		//文字表示

		//背景スクロール
		P_Grp			m_scroll_bgm;
		float			m_scrlbgm_x { 0 };

	public:
		CharaSele_BGM ();
		CharaSele_BGM ( const CharaSele_BGM & rhs ) = delete;
		~CharaSele_BGM ();

		void Move ();

		void On ();
		void Off ();

		void Prev ();
		void Next ();
		void Decide ();

		void Set_BGM_ID ( BGM_ID id );
		BGM_ID Get_ID () const { return m_bgm_id; }

	private:
#pragma region CONST
		static const float BGM_SCROLL_X;
		static const float BGM_SCROLL_Y;
		static const float BGM_X;
		static const float BGM_Y;
		static const float BGM_TRI_X;
		static const float BGM_TRI_Y;
		static const float TXT_BGM_X;
		static const float TXT_BGM_Y;
#pragma endregion
	};

	using P_CharaSele_BGM = std::shared_ptr < CharaSele_BGM >;


}	//namespace GAME

