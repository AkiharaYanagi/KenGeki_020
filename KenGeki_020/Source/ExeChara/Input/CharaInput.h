//=================================================================================================
//
// CharaInput ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Chara.h"
#include "../../GameMain/GameConst.h"
#include "../../FtgMain/FtgConst.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class CharaInput
	{
		static const UINT	m_vGameKeyNum;	//キー入力の保存フレーム数
		V_GAME_KEY			m_vGameKey;		//キー入力保存
		PLAYER_ID			m_playerID;		//プレイヤーID
		bool				m_cpu;			//CPUフラグ

		//コマンドが完成したIDを優先順に保存したリスト
		V_UINT				m_vCompID;		

	public:
		CharaInput ();
		CharaInput ( const CharaInput& rhs ) = delete;		//コピー禁止
		virtual ~CharaInput ();

		//プレイヤーID
		void SetPlayer ( PLAYER_ID id ) { m_playerID = id; }

		//読込
		virtual void Load () {}

		//フレーム毎における入力の保存
		virtual void Update ( bool dirRight );

		//入力をクリア
		void ClearInput ();

		//入力を一つ進める(過去に記録)
		void IncrementInput ( GameKey & gameKey );


		//キー入力配列の参照
		const V_GAME_KEY & GetvGameKey () const { return m_vGameKey; }
		V_GAME_KEY & GetvGameKey () { return m_vGameKey; }

		//ルートリストをチェックして各種ブランチのコマンドが達成されていたら
		//遷移先のアクションIDを返す
		//戻値：enum { NO_COMPLETE (0xFFFFFFFF) } 不成立
		virtual UINT GetTransitID ( const Chara & ch, P_Script pScp, bool dirRight );

		//成立リストを生成する
		virtual void MakeTransitIDList ( const Chara & ch, P_Script pScp, bool dirRight );
		virtual void MakeTransitIDList ( const Chara & ch, V_UINT vBrc, bool dirRight );
 
		//キーの保存
		void SetGameKey ( V_GAME_KEY & vKey );

		//優先リストの先頭を取得する
		UINT GetCompID ();

		//優先リストの参照を得る
		const std::vector < UINT > & GetvCompID () const { return m_vCompID; }


		//直接キー取得
		bool IsLvr4 () const { return m_vGameKey[0].GetLvr ( GameKey::LVR_4 ); }
		bool IsLvr3 () const { return m_vGameKey[0].GetLvr ( GameKey::LVR_3 ); }

		//何れかのキーが入力されているかどうか
		bool IsSomething () const;

		//何れかのキーが押された瞬間かどうか
		bool PushSomething () const;
	};

	using P_CharaInput = std::shared_ptr < CharaInput >;


}	//namespace GAME


