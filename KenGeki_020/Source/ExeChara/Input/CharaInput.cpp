//=================================================================================================
//
// CharaInput ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaInput.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//static実体
	const UINT CharaInput::m_vGameKeyNum = 60;		//キー入力の保存フレーム数

	//コンストラクタ
	CharaInput::CharaInput ()
		: m_playerID ( PLAYER_ID_1 ), m_cpu ( F )
	{
		for ( UINT i = 0; i < m_vGameKeyNum; ++i )
		{
			GameKey gameKey;
			m_vGameKey.push_back ( gameKey );
		}
	}

	//デストラクタ
	CharaInput::~CharaInput ()
	{
	}

	//更新
	void CharaInput::Update ( bool dirRight )
	{
		//今回の入力をゲームキーに直して保存
		GameKey gameKey;

		//上下前後
		bool bKey8 = F;	//上
		bool bKey2 = F;	//下
		bool bKey4 = F;	//後(右向き時)
		bool bKey6 = F;	//前(右向き時)

		if ( PLAYER_ID_1 == m_playerID )
		{
			bKey8 = CFG_IS_KEY ( P1_UP );
			bKey2 = CFG_IS_KEY ( P1_DOWN );
			if ( dirRight )	//右向き時
			{
				bKey4 = CFG_IS_KEY ( P1_LEFT );
				bKey6 = CFG_IS_KEY ( P1_RIGHT );
			}
			else	//左向き時
			{
				bKey4 = CFG_IS_KEY ( P1_RIGHT );
				bKey6 = CFG_IS_KEY ( P1_LEFT );
			}
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			bKey8 = CFG_IS_KEY ( P2_UP );
			bKey2 = CFG_IS_KEY ( P2_DOWN );
			if ( dirRight )	//右向き時
			{
				bKey4 = CFG_IS_KEY ( P2_LEFT );
				bKey6 = CFG_IS_KEY ( P2_RIGHT );
			}
			else	//左向き時
			{
				bKey4 = CFG_IS_KEY ( P2_RIGHT );
				bKey6 = CFG_IS_KEY ( P2_LEFT );
			}
		}

		//3つ以上同時押しは優先順で処理

		// コマンド指定では12369874順

		//斜め優先
		if ( bKey4 && bKey2 )	{ gameKey.SetLvr ( GameKey::LVR_1, T ); }
		if ( bKey2 )			{ gameKey.SetLvr ( GameKey::LVR_2, T ); }
		if ( bKey6 && bKey2 )	{ gameKey.SetLvr ( GameKey::LVR_3, T ); }
		if ( bKey6 )			{ gameKey.SetLvr ( GameKey::LVR_6, T ); }
		if ( bKey8 && bKey6 )	{ gameKey.SetLvr ( GameKey::LVR_9, T ); }
		if ( bKey8 )			{ gameKey.SetLvr ( GameKey::LVR_8, T ); }
		if ( bKey8 && bKey4 )	{ gameKey.SetLvr ( GameKey::LVR_7, T ); }
		if ( bKey4 )			{ gameKey.SetLvr ( GameKey::LVR_4, T ); }


		//==============================================================================
		//ボタン
		bool bBtn0 = F; bool bBtn1 = F; bool bBtn2 = F; bool bBtn3 = F;
		bool bBtn4 = F; bool bBtn5 = F; bool bBtn6 = F; bool bBtn7 = F;

		if ( PLAYER_ID_1 == m_playerID )
		{
			bBtn0 = CFG_IS_KEY ( P1_BTN0 );
			bBtn1 = CFG_IS_KEY ( P1_BTN1 );
			bBtn2 = CFG_IS_KEY ( P1_BTN2 );
			bBtn3 = CFG_IS_KEY ( P1_BTN3 );
			bBtn4 = CFG_IS_KEY ( P1_BTN4 );
			bBtn5 = CFG_IS_KEY ( P1_BTN5 );
			bBtn6 = CFG_IS_KEY ( P1_BTN6 );
			bBtn7 = CFG_IS_KEY ( P1_BTN7 );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			bBtn0 = CFG_IS_KEY ( P2_BTN0 );
			bBtn1 = CFG_IS_KEY ( P2_BTN1 );
			bBtn2 = CFG_IS_KEY ( P2_BTN2 );
			bBtn3 = CFG_IS_KEY ( P2_BTN3 );
			bBtn4 = CFG_IS_KEY ( P2_BTN4 );
			bBtn5 = CFG_IS_KEY ( P2_BTN5 );
			bBtn6 = CFG_IS_KEY ( P2_BTN6 );
			bBtn7 = CFG_IS_KEY ( P2_BTN7 );
		}


		gameKey.SetBtn ( 0, bBtn0 );
		gameKey.SetBtn ( 1, bBtn1 );
		gameKey.SetBtn ( 2, bBtn2 );
		gameKey.SetBtn ( 3, bBtn3 );
		gameKey.SetBtn ( 4, bBtn4 );
		gameKey.SetBtn ( 5, bBtn5 );
		gameKey.SetBtn ( 6, bBtn6 );
		gameKey.SetBtn ( 7, bBtn7 );

		//状態を１つ進める
		IncrementInput ( gameKey );
	}


	void CharaInput::ClearInput ()
	{
		//@info clear()は配列を０にする
		//m_vGameKey.clear ();

		for ( size_t i = 0; i < m_vGameKeyNum; ++ i )
		{
			m_vGameKey [ i ].ClearKey ();
		}
	}

	void CharaInput::IncrementInput ( GameKey & gameKey )
	{
		//前回のキーを保存する
		gameKey.ReservePrevious ( m_vGameKey[0] );


		//ゲーム入力を更新しながら現在フレーム分を保存
		for ( int i = m_vGameKeyNum - 1; i >= 1; -- i )
		{
			m_vGameKey[i] = m_vGameKey[i - 1];
		}
		m_vGameKey[0] = gameKey;	//最後に先頭に記録
	}



	//------------------------------------------------------------------------------------
	//ルートリストをチェックして各種ブランチのコマンドが達成されていたら
	//遷移先のアクションIDを返す
	//戻値：enum { NO_COMPLETE (0xFFFFFFFF) } 不成立
	UINT CharaInput::GetTransitID ( const Chara & ch, P_Script pScp, bool dirRight )
	{
		//キャラの持つルート,ブランチ,コマンドの参照
		const VP_Route vpRoute = ch.GetvpRoute ();
		const VP_Branch vpBranch = ch.GetvpBranch ();
		const VP_Command vpCommand = ch.GetvpCommand ();
		
		//スクリプトの持つルートリスト
		for ( UINT indexRoute : pScp->GetcvRouteID () )
		{
			const V_UINT vBranchID = vpRoute[indexRoute]->GetcvIDBranch ();

			//対象のブランチリスト
			for ( UINT indexBranch : vBranchID )
			{
				//コマンド分岐以外は飛ばす
				if ( BRC_CMD != vpBranch[indexBranch]->GetCondition () ) { continue; }

				//コマンド取得
				UINT indexCommand = vpBranch[indexBranch]->GetIndexCommand ();
				P_Command pCmd = vpCommand[indexCommand];

				//対象コマンドが成立していたら
				if ( pCmd->Compare ( m_vGameKey, dirRight ) )
				{
					//遷移先アクションIDを返す
					return vpBranch[indexBranch]->GetIndexSequence ();
				}
			}
		}
		//不成立のとき
		return (UINT)NO_COMPLETE;
	}

	
	//成立リストを生成する
	void CharaInput::MakeTransitIDList ( const Chara & ch, P_Script pScp, bool dirRight )
	{
		//成立した１つのIDではなく、成立したIDを優先順位で保存したリストを返す
		m_vCompID.clear ();

		//キャラの持つルート,ブランチ,コマンドの参照
		const VP_Route vpRoute = ch.GetvpRoute ();
		const VP_Branch vpBranch = ch.GetvpBranch ();
		const VP_Command vpCommand = ch.GetvpCommand ();

		//スクリプトの持つルートリスト
		for ( UINT indexRoute : pScp->GetcvRouteID () )
		{
			//ルートの取得
			P_Route pRut = vpRoute [ indexRoute ];
			const V_UINT vBranchID = vpRoute [ indexRoute ]->GetcvIDBranch ();

			//対象のブランチリスト
			for ( UINT indexBranch : vBranchID )
			{
				//ブランチの取得
				P_Branch pBrc = vpBranch [ indexBranch ];

				//コマンド分岐以外は飛ばす
				if ( BRC_CMD != pBrc->GetCondition () ) { continue; }

				//コマンドの取得
				UINT indexCommand = vpBranch [ indexBranch ]->GetIndexCommand ();
				P_Command pCmd = vpCommand [ indexCommand ];

				//対象コマンドが成立していたら
				if ( pCmd->Compare ( m_vGameKey, dirRight ) )
				{
					//遷移先アクションIDを登録する
					UINT id = vpBranch [ indexBranch ]->GetIndexSequence ();
					m_vCompID.push_back ( id );
				}
			}
#if 0
			MakeTransitIDList ( ch, vBranchID, dirRight );
#endif // 0
		}
	}
	
	
	//成立リストを生成する
	//引数：キャラ参照, 特定条件のブランチIDリスト, 向き
	void CharaInput::MakeTransitIDList ( const Chara & ch, V_UINT vBrc, bool dirRight )
	{
		//成立した１つのIDではなく、成立したIDを優先順位で保存したリストを返す
		m_vCompID.clear ();

		//キャラの持つルート,ブランチ,コマンドの参照
		const VP_Route vpRoute = ch.GetvpRoute ();
		const VP_Branch vpBranch = ch.GetvpBranch ();
		const VP_Command vpCommand = ch.GetvpCommand ();


		//対象のブランチリスト
		//特定条件のブランチIDリスト
		for ( UINT indexBranch : vBrc )
		{
			//ブランチの取得
			P_Branch pBrc = vpBranch [ indexBranch ];

			//コマンド分岐以外は飛ばす
			if ( BRC_CMD != pBrc->GetCondition () ) { continue; }

			//コマンドの取得
			UINT indexCommand = vpBranch [ indexBranch ]->GetIndexCommand ();
			P_Command pCmd = vpCommand [ indexCommand ];

			//対象コマンドが成立していたら
			if ( pCmd->Compare ( m_vGameKey, dirRight ) )
			{
				//遷移先アクションIDを登録する
				UINT id = vpBranch [ indexBranch ]->GetIndexSequence ();
				m_vCompID.push_back ( id );
			}
		}
	}


	//優先リストの先頭を取得する
	UINT CharaInput::GetCompID ()
	{
		if ( m_vCompID.size() > 0 )
		{
			return m_vCompID [ 0 ];
		}
		return (UINT)NO_COMPLETE;
	}

	void CharaInput::SetGameKey ( V_GAME_KEY & vKey )
	{
		size_t size = m_vGameKey.size ();
		for ( size_t i = 0; i < size; ++ i )
		{
			m_vGameKey [ i ] = vKey [ i ];
		}
	}


	bool CharaInput::IsSomething () const
	{
		if ( m_vGameKey [ 0 ].GetLvr ( GameKey::LVR_1 ) ) { return T; }
		if ( m_vGameKey [ 0 ].GetLvr ( GameKey::LVR_2 ) ) { return T; }
		if ( m_vGameKey [ 0 ].GetLvr ( GameKey::LVR_3 ) ) { return T; }
		if ( m_vGameKey [ 0 ].GetLvr ( GameKey::LVR_6 ) ) { return T; }
		if ( m_vGameKey [ 0 ].GetLvr ( GameKey::LVR_9 ) ) { return T; }
		if ( m_vGameKey [ 0 ].GetLvr ( GameKey::LVR_8 ) ) { return T; }
		if ( m_vGameKey [ 0 ].GetLvr ( GameKey::LVR_7 ) ) { return T; }
		if ( m_vGameKey [ 0 ].GetLvr ( GameKey::LVR_4 ) ) { return T; }

		if ( m_vGameKey [ 0 ].GetBtn ( GameKey::BTN_0 ) ) { return T; }
		if ( m_vGameKey [ 0 ].GetBtn ( GameKey::BTN_1 ) ) { return T; }
		if ( m_vGameKey [ 0 ].GetBtn ( GameKey::BTN_2 ) ) { return T; }
		if ( m_vGameKey [ 0 ].GetBtn ( GameKey::BTN_3 ) ) { return T; }
		if ( m_vGameKey [ 0 ].GetBtn ( GameKey::BTN_4 ) ) { return T; }
		if ( m_vGameKey [ 0 ].GetBtn ( GameKey::BTN_5 ) ) { return T; }
		if ( m_vGameKey [ 0 ].GetBtn ( GameKey::BTN_6 ) ) { return T; }
		if ( m_vGameKey [ 0 ].GetBtn ( GameKey::BTN_7 ) ) { return T; }

		return F;
	}

}	//namespace GAME

