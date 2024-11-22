//=================================================================================================
//
// ExeEffect ヘッダファイル
//		Effect１つにつき１個のオブジェクトを生成し実行する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Chara.h"
#include "DispEffect.h"
#include "../Rect/CharaRect.h"
#include "../BtlParam.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class ExeEffect : public TASK_VEC
	{
		//------------------------------------------------
		P_Effect		m_pEffect;		//実効エフェクトポインタ

		P_Chara			m_pChara;		//キャラ
		VP_Branch		m_vpBranch;		//エフェクトの分岐
		VP_Route		m_vpRoute;		//ルート

		//------------------------------------------------
		P_DispEffect	m_dispEffect;	//表示項目管理
		bool			m_bDispRect;	//枠表示

		//------------------------------------------------
		//パラメータ
		bool		m_active;		//有効フラグ
		bool		m_end;			//終了フラグ

		UINT		m_frame;		//実効内部フレーム(スクリプトID)
		P_Script	m_pScript;		//実効スクリプトポインタ
		VEC2		m_ptEffect;		//エフェクト位置

		VEC2		m_ptGnrt;		//エフェクト発生位置
		bool		m_gnrt;			//生成
		bool		m_loop;			//繰返
		bool		m_sync;			//同期

		bool		m_dirRight;	//エフェクトの向き
		VEC2		m_vel;	//速度
		VEC2		m_acc;	//加速度

		P_CharaRect		m_charaRect;	//枠

		bool		m_offset;		//相殺
		bool		m_hit;			//ヒット

	public:
		ExeEffect ( P_Effect pEffect, P_Chara pChara, P_EfGnrt pEfGnrt, VEC2 ptChara, bool dirRight );
		ExeEffect ( const ExeEffect & rhs ) = delete;
		~ExeEffect ();

		void Init ();

		void Disp ();	//復旧時表示のみ

		//---------------------------------------------
		//枠取得
		P_CharaRect GetpCharaRect () { return m_charaRect; }
		//---------------------------------------------

		void SetpEfGnrt ( P_EfGnrt p );

		P_Effect GetpEffect () const { return m_pEffect; }
		bool Compare ( P_Effect p ) { return ( p == m_pEffect); }

		bool IsActive () const { return m_active; }
		bool IsEnd () const { return m_end; }

		P_Script GetpScript ()
		{
			return m_pEffect->GetpScript ( m_frame );
		}

		//稼働開始
		void Drive () { m_active = true; }

		//稼働停止
		void Stop ()
		{
			m_active = false;
			m_dispEffect->SetValid ( false );
		}

		void PreScriptMove ();
		void PostScriptMove ( BtlParam & btlprm );
		void SynchroScript ( VEC2 ptChara );

		//値の設定
//		void SetZ ( float z ) { m_dispEffect.SetZ ( z ); }
		void SetShader ( bool b ) { m_dispEffect->SetShader ( b ); }


		//相殺
		void SetOffset ( bool b ) { m_offset = b; }
		bool GetOffset () const { return m_offset; }

		//ヒット
		void SetHit ( bool b ) { m_hit = b; }
		bool GetHit () const { return m_hit; }

		//---------------------------------------------------------------
		//Rect
		void OnDispRect () { m_bDispRect = true; }
		void OffDispRect () { m_bDispRect = false; }

	private :
		//xだけ向きを反映する
		VEC2 Dir ( VEC2 v ) const
		{
			if ( m_dirRight ) { return v; }
			return VEC2 ( -v.x, v.y );
		}

		void CalcPos ();
	};

	//型別定義 エイリアス
	using ExEf = ExeEffect;
	using P_ExEf = std::shared_ptr < ExEf >;

	using VP_ExEf = std::vector < P_ExEf >;
	using PVP_ExEf = std::shared_ptr < VP_ExEf >;

	using LP_ExEf = std::list < P_ExEf >;
	using PLP_ExEf = std::shared_ptr < LP_ExEf >;


}	//namespace GAME


