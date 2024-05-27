//=================================================================================================
//
// LoadCharaFunc ソースファイル
//
//=================================================================================================
#include "LoadCharaBinFunc.h"

//#include <codecvt>

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	LoadCharaBinFunc::LoadCharaBinFunc ()
	{
	}


	void LoadCharaBinFunc::LoadChara ( UP_BYTE buf, UINT & pos, Chara & ch )
	{
		LoadCharaScript ( std::move ( buf ), pos, ch );
		LoadCharaImage ( std::move ( buf ), pos, ch );
	}

	void LoadCharaBinFunc::LoadCharaScript ( UP_BYTE buf, UINT & pos, Chara & ch )
	{
		LoadBehavior ( std::move ( buf ), pos, ch );	//Behavior
		LoadGarnish ( std::move ( buf ), pos, ch );	//Garnish
		LoadCommand ( std::move ( buf ), pos, ch );	//Command
		LoadBranch ( std::move ( buf ), pos, ch );	//Branch
		LoadRoute ( std::move ( buf ), pos, ch );		//Route
	}

	void LoadCharaBinFunc::LoadCharaImage ( UP_BYTE buf, UINT & pos, Chara & ch )
	{
		LoadImg ( std::move ( buf ), pos, ch.GetpapTxMain () );
		LoadImg ( std::move ( buf ), pos, ch.GetpvpEfTexture () );
#if 0
#endif // 0
	}


	void LoadCharaBinFunc::LoadBehavior ( UP_BYTE buf, UINT & pos, Chara & ch )
	{
		//@afford メモリコントローラ
		//先頭に 総アクション数, 総スクリプト数 を記述、必要時に該当分のアドレスを返す

		//アクション個数 と メモリの確保
		UINT nAct = m_utl.LoadUInt ( std::move ( buf ), pos );

#if 0
		unique_ptr < Action [] > pi = make_unique < Action [] > ( nAct );

		unique_ptr < P_Action [] > aryAct = make_unique < P_Action [] > ( nAct );
//		for ( UINT i = 0; i < nAct; ++ i ) { aryAct [ i ] = make_shared < Action > (); }

		std::shared_ptr < P_Action [] > aryShared { new P_Action [ nAct ] , default_delete < P_Action [] > () };
		for ( UINT i = 0; i < nAct; ++ i ) { aryAct [ i ] = aryShared [ i ]; }
#endif // 0
#if 0
		unique_ptr < P_Action [] > aryAct = make_unique < P_Action [] > ( nAct );
		std::shared_ptr < Action [] > aryShared = make_shared < Action [] > ( nAct );
		for ( UINT i = 0; i < nAct; ++ i ) { aryAct [ i ].reset ( & aryShared [ i ] ); }
#endif // 0


		std::unique_ptr < P_Action [] > aryAct = std::make_unique < P_Action [] > ( nAct );
//		std::vector < P_Action > aryAct ( nAct );
		for ( UINT i = 0; i < nAct; ++ i ) { aryAct [ i ] = std::make_shared < Action > (); }


		//実データ
		for ( UINT iAct = 0; iAct < nAct; ++ iAct )
		{
			P_Action pAct = aryAct [ iAct ];

			//アクション
			aryAct [ iAct ]->SetName ( m_utl.LoadS3dString ( std::move ( buf ), pos ) );


//			TRACE_F ( _T ( "LoadCharaBin: %s\n" ), pAct->GetName ().c_str () );
//			TRACE_F ( _T ( "LoadCharaBin: %d\n" ), iAct );


			aryAct [ iAct ]->SetNextID ( (UINT)m_utl.LoadUInt ( std::move ( buf ), pos ) );
			aryAct [ iAct ]->SetCategory ( (ACTION_CATEGORY)buf [ pos ++ ] );
			aryAct [ iAct ]->SetPosture ( (ACTION_POSTURE)buf [ pos ++ ] );
			aryAct [ iAct ]->SetHitNum ( (UINT)buf [ pos ++ ] );
			aryAct [ iAct ]->SetHitPitch ( (UINT)buf [ pos ++ ] );
			aryAct [ iAct ]->SetBalance ( m_utl.LoadInt ( std::move ( buf ), pos ) );

			//スクリプト個数 と メモリの確保
			UINT nScp = m_utl.LoadUInt ( std::move ( buf ), pos );

			std::unique_ptr < P_Script [] > aryScp = std::make_unique < P_Script [] > ( nScp );
			for ( UINT i = 0; i < nScp; ++ i ) { aryScp [ i ] = std::make_shared < Script > (); }

			for ( UINT iScp = 0; iScp < nScp; ++ iScp )
			{
				aryScp [ iScp ]->SetFrame ( iScp );
				LoadScript ( std::move ( buf ), pos, (* aryScp [ iScp ]) );
			}

			aryAct [ iAct ]->AddaScript ( std::move (aryScp), nScp );
		}

//		ch.AddpAction ( aryAct, nAct );
		ch.AddpAction ( std::move ( aryAct ), nAct );

	}


#if 0
#endif // 0

	
	void LoadCharaBinFunc::LoadGarnish ( UP_BYTE buf, UINT & pos, Chara & ch )
	{
		//エフェクト個数 と メモリの確保
		UINT nEfc = m_utl.LoadUInt ( std::move ( buf ), pos );

		std::vector < P_Effect > aryEfc( nEfc );
		for ( UINT i = 0; i < nEfc; ++ i ) { aryEfc [ i ] = std::make_shared < Effect > (); }

		//実データ
		for ( UINT iEfc = 0; iEfc < nEfc; ++ iEfc )
		{
			//エフェクト
			aryEfc [ iEfc ]->SetName ( m_utl.LoadS3dString ( std::move ( buf ), pos ) );

			//スクリプト個数 と メモリの確保
			UINT nScp = m_utl.LoadUInt ( std::move ( buf ), pos );
			std::unique_ptr < P_Script [] > aryScp = std::make_unique < P_Script [] > ( nScp );
			for ( UINT i = 0; i < nScp; ++ i ) { aryScp [ i ] = std::make_shared < Script > (); }

			for ( UINT iScp = 0; iScp < nScp; ++ iScp )
			{
				aryScp [ iScp ]->SetFrame ( iScp );
				LoadScript ( std::move ( buf ), pos, ( * aryScp [ iScp ] ) );
			}

			aryEfc [ iEfc ]->AddaScript ( std::move ( aryScp ), nScp );
		}

		ch.AddpEffect ( aryEfc, nEfc );
	}

	void LoadCharaBinFunc::LoadCommand ( UP_BYTE buf, UINT & pos, Chara & ch )
	{
		//コマンド個数 と メモリの確保
		UINT nCmd = m_utl.LoadUInt ( std::move ( buf ), pos );
		std::unique_ptr < P_Command[] > aryCmd = std::make_unique < P_Command[] > ( nCmd );
		for ( UINT i = 0; i < nCmd; ++ i ) { aryCmd [ i ] = std::make_shared < Command > (); }

		//実データ
		for ( UINT i = 0; i < nCmd; ++ i )
		{
			//コマンド名
			s3d::String str = m_utl.LoadS3dString ( std::move ( buf ), pos );
			aryCmd [ i ]->SetName ( str );

			//受付時間[byte]
			byte lmtTime = buf [ pos ++ ];
			aryCmd [ i ]->SetLimitTime ( (UINT)lmtTime );

			//ゲームキー
			byte nGameKey = buf [ pos ++ ];
			std::unique_ptr < GameKeyCommand [] > gkc = std::make_unique < GameKeyCommand [] > ( nGameKey );
			for ( UINT iKey = 0; iKey < nGameKey; ++ iKey )
			{
				//否定
//				bool bNot = (bool)buf [ pos ++ ];
				bool bNot = m_utl.LoadBool ( std::move ( buf ), pos );

				//レバー [ GameKey::LVR_NUM = 8 ]
				KEY_ST lvr [ GameKey::LVR_NUM ] = { GameKeyCommand::GAME_KEY_WILD };
				for ( UINT iLvr = 0; iLvr < GameKey::LVR_NUM; ++ iLvr )
				{
					lvr [ iLvr ] = (KEY_ST)buf [ pos ++ ];
				}

				//ボタン [ _GameKey::BTN_NUM = 8 ]
				KEY_ST btn [ GameKey::BTN_NUM ] = { GameKeyCommand::GAME_KEY_WILD };
				for ( UINT iBtn = 0; iBtn < GameKey::BTN_NUM; ++ iBtn )
				{
					btn [ iBtn ] = (KEY_ST)buf [ pos ++ ];
				}

				gkc [ iKey ].SetNot ( bNot );
				gkc [ iKey ].SetaLvr ( lvr );
				gkc [ iKey ].SetaBtn ( btn );
			}

			aryCmd [ i ]->SetaGameKey ( gkc.get (), nGameKey );
		}

		ch.AddaCommand ( std::move ( aryCmd ), nCmd );
	}


	void LoadCharaBinFunc::LoadBranch ( UP_BYTE buf, UINT & pos, Chara & ch )
	{
		//ブランチ個数 と メモリの確保
		UINT nBrc = m_utl.LoadUInt ( std::move ( buf ), pos );
		std::unique_ptr < P_Branch [] > aryBrc = std::make_unique < P_Branch [] > ( nBrc );
		for ( UINT i = 0; i < nBrc; ++ i ) { aryBrc [ i ] = std::make_shared < Branch > (); }

		//実データ
		for ( UINT i = 0; i < nBrc; ++ i )
		{
			P_Branch brc = aryBrc [ i ];

			//ブランチ名
			brc->SetName ( m_utl.LoadS3dString ( std::move ( buf ), pos ) );

			//条件
			brc->SetCondition ( (BRANCH_CONDITION)buf [ pos ++ ] );
			brc->SetIndexCommand ( m_utl.LoadUInt ( std::move ( buf ), pos ) );
			brc->SetIndexSequence ( m_utl.LoadUInt ( std::move ( buf ), pos ) );
			brc->SetIndexFrame ( m_utl.LoadUInt ( std::move ( buf ), pos ) );
			brc->SetOther ( m_utl.LoadBool ( std::move ( buf ), pos ) );
		}
		ch.AddaBranch ( std::move ( aryBrc ), nBrc );
	}


	void LoadCharaBinFunc::LoadRoute ( UP_BYTE buf, UINT & pos, Chara & ch )
	{
		//ルート個数 と メモリの確保
		UINT nRut = m_utl.LoadUInt ( std::move ( buf ), pos );
		std::unique_ptr < P_Route [] > aryRut = std::make_unique < P_Route [] > ( nRut );
		for ( UINT i = 0; i < nRut; ++ i ) { aryRut [ i ] = std::make_shared < Route > (); }

		//実データ
		for ( UINT i = 0; i < nRut; ++ i )
		{
			P_Route pr = aryRut [ i ];

			//ルート名
			aryRut [ i ]->SetName ( m_utl.LoadS3dString ( std::move ( buf ), pos ) );

			//ブランチIDリスト
			m_utl.LoadAryUint ( std::move ( buf ), pos, aryRut [ i ]->GetvIDBranch () );
		}

		ch.AddaRoute ( std::move ( aryRut ), nRut );
	}

	void LoadCharaBinFunc::LoadScript ( UP_BYTE buf, UINT & pos, Script & scp )
	{
		//イメージインデックス
		UINT imdIndex = m_utl.LoadUInt ( std::move ( buf ), pos );
		scp.SetImageIndex ( (UINT)imdIndex );

		//位置
		scp.SetPos ( m_utl.LoadVec2 ( std::move ( buf ), pos ) );

		// [] ルートID
		m_utl.LoadAryUint ( std::move ( buf ), pos, scp.GetvRouteID () );

		//枠
		m_utl.LoadListRect ( std::move ( buf ), pos, scp.GetpvCRect () );
		m_utl.LoadListRect ( std::move ( buf ), pos, scp.GetpvHRect () );
		m_utl.LoadListRect ( std::move ( buf ), pos, scp.GetpvARect () );
		m_utl.LoadListRect ( std::move ( buf ), pos, scp.GetpvORect () );

		// [] エフェクト生成
		UINT nIdEfGnrt = m_utl.LoadUInt ( std::move ( buf ), pos );
		for ( UINT i = 0; i < nIdEfGnrt; ++ i )
		{
			//設定用
			P_EfGnrt pEfGnrt = std::make_shared < EffectGenerate > ();

			//エフェクトID
			pEfGnrt->SetIndex ( m_utl.LoadUInt ( std::move ( buf ), pos ) );
			//位置
			int pos_x = m_utl.LoadInt ( std::move ( buf ), pos );
			int pos_y = m_utl.LoadInt ( std::move ( buf ), pos );
			pEfGnrt->SetPos ( VEC2 ( (float)pos_x, (float)pos_y ) );
			//Z値
			int z_per100F = (int)m_utl.LoadInt ( std::move ( buf ), pos );
			pEfGnrt->SetZ ( z_per100F * 0.01f );
			//生成
			pEfGnrt->SetGnrt ( (bool)buf [ pos ++ ] );
			//ループ
			pEfGnrt->SetLoop ( (bool)buf [ pos ++ ] );
			//位置同期
			pEfGnrt->SetSync ( (bool)buf [ pos ++ ] );

			//スクリプトに設定
			scp.GetpvpEfGnrt ()->push_back ( pEfGnrt );
		}

		//バトルパラメータ
		LoadScpPrm_Btl ( std::move ( buf ), pos, scp );

		//ステージング(演出)パラメータ
		LoadScpPrm_Stg ( std::move ( buf ), pos, scp );
	}


	//スクリプト・戦闘パラメータ
	void LoadCharaBinFunc::LoadScpPrm_Btl ( UP_BYTE buf, UINT & pos, Script & scp )
	{
		scp.m_prmBattle.CalcState = (CLC_ST)m_utl.LoadInt ( std::move ( buf ), pos );

		//@info 移動量を0.1f倍する
//		scp.m_prmBattle.Vel = m_utl.LoadVec2 ( buf, pos );
//		scp.m_prmBattle.Acc = m_utl.LoadVec2 ( buf, pos );
		scp.m_prmBattle.Vel = m_utl.LoadVec2_Dev10F ( std::move ( buf ), pos );
		scp.m_prmBattle.Acc = m_utl.LoadVec2_Dev10F ( std::move ( buf ), pos );

		scp.m_prmBattle.Power = m_utl.LoadInt ( std::move ( buf ), pos );

		scp.m_prmBattle.Warp = m_utl.LoadInt ( std::move ( buf ), pos );
		scp.m_prmBattle.Recoil_I = m_utl.LoadInt ( std::move ( buf ), pos );
		scp.m_prmBattle.Recoil_E = m_utl.LoadInt ( std::move ( buf ), pos );
		scp.m_prmBattle.Balance_I = m_utl.LoadInt ( std::move ( buf ), pos );
		scp.m_prmBattle.Balance_E = m_utl.LoadInt ( std::move ( buf ), pos );
	}


	//スクリプト・演出パラメータ
	void LoadCharaBinFunc::LoadScpPrm_Stg ( UP_BYTE buf, UINT & pos, Script & scp )
	{
		scp.m_prmStaging.BlackOut		 = m_utl.LoadByte ( std::move ( buf ), pos );
		scp.m_prmStaging.Vibration		 = m_utl.LoadByte ( std::move ( buf ), pos );
		scp.m_prmStaging.Stop			 = m_utl.LoadByte ( std::move ( buf ), pos );

		scp.m_prmStaging.Rotate			 = m_utl.LoadInt ( std::move ( buf ), pos );
		scp.m_prmStaging.Rotate_center	 = m_utl.LoadVec2 ( std::move ( buf ), pos );
		scp.m_prmStaging.AfterImage_N	 = m_utl.LoadByte ( std::move ( buf ), pos );
		scp.m_prmStaging.AfterImage_time = m_utl.LoadByte ( std::move ( buf ), pos ); ;
		scp.m_prmStaging.AfterImage_pitch = m_utl.LoadByte ( std::move ( buf ), pos ); ;
		scp.m_prmStaging.Vibration_S	 = m_utl.LoadByte ( std::move ( buf ), pos );;
		scp.m_prmStaging.Color			 = (_CLR)m_utl.LoadUInt ( std::move ( buf ), pos );
		scp.m_prmStaging.Color_time		 = m_utl.LoadByte ( std::move ( buf ), pos );

		scp.m_prmStaging.Scaling		 = m_utl.LoadVec2 ( std::move ( buf ), pos );
		scp.m_prmStaging.SE				 = m_utl.LoadUInt ( std::move ( buf ), pos );
	}


	//イメージ
	void LoadCharaBinFunc::LoadImg ( UP_BYTE buf, UINT & pos, PAP_Tx pvpTx )
	{
		//個数
		UINT nImg = m_utl.LoadUInt ( std::move ( buf ), pos );
		pvpTx->clear ();
		pvpTx->resize ( nImg );

		for ( UINT i = 0; i < nImg; ++ i )
		{
			//サイズを取得
			UINT size = m_utl.LoadUInt ( std::move ( buf ), pos );

			UINT temp_pos = pos;
#if 0
			byte b0 = buf [ pos ++ ];
			byte b1 = buf [ pos ++ ];
			byte b2 = buf [ pos ++ ];
			byte b3 = buf [ pos ++ ];
#endif // 0

			pos = temp_pos + size;

			//メモリ上のデータからゲームテクスチャに変換
//			s3d::Image img ();


#if 0
			P_Tx pTx = std::make_shared < s3d::Texture > ( (LPCVOID)(buf.get() + pos), size );
			pos += size;


			s3d::BinaryReader br;

			//キャラ内部のテクスチャリストに加える
			( *pvpTx ) [ i ] = pTx;
#endif
		}

	}




}	//namespace GAME

