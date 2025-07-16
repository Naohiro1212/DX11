#include "Quad.h"
#include "Texture.h"

Quad::Quad() : pVertexBuffer_(NULL), pIndexBuffer_(NULL), pConstantBuffer_(NULL), pTexture_(NULL)
{
	// メンバいないからスルー
}

Quad::~Quad()
{
}

HRESULT Quad::Initialize()
{
	HRESULT hr;
	// 頂点情報
	
	//XMVECTOR vertices[] =
	//{
	//	XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),	// 四角形の頂点（左上）
	//	XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	// 四角形の頂点（右上）
	//	XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	// 四角形の頂点（右下）
	//	XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),	// 四角形の頂点（左下）		
	//};

	// 頂点情報
	VERTEX vertices[] =
	{
		// 前面1
		{ XMVectorSet(-1,  1, -1, 1), XMVectorSet(0.00f, 0.0f, 0, 0), XMVectorSet(0, 0, -1.0, 0)}, // 左上
		{ XMVectorSet(1,  1, -1, 1),  XMVectorSet(0.25f, 0.0f, 0, 0), XMVectorSet(0, 0, -1.0, 0) }, // 右上
		{ XMVectorSet(1, -1, -1, 1),  XMVectorSet(0.25f, 0.5f, 0, 0), XMVectorSet(0, 0, -1.0, 0)}, // 右下
		{ XMVectorSet(-1, -1, -1, 1), XMVectorSet(0.00f, 0.5f, 0, 0), XMVectorSet(0, 0, -1.0, 0) }, // 左下
		// 右面2
		{ XMVectorSet(1,  1, -1, 1),  XMVectorSet(0.25f, 0.0f, 0, 0), XMVectorSet(1.0, 0, 0, 0) }, // 左上
		{ XMVectorSet(1,  1, 1, 1),   XMVectorSet(0.50f, 0.0f, 0, 0), XMVectorSet(1.0, 0, 0, 0) }, // 右上
		{ XMVectorSet(1, -1,  1, 1),  XMVectorSet(0.50f, 0.5f, 0, 0), XMVectorSet(1.0, 0, 0, 0) }, // 右下
		{ XMVectorSet(1, -1, -1, 1),  XMVectorSet(0.25f, 0.5f, 0, 0), XMVectorSet(1.0, 0, 0, 0) }, // 左下
		// 背面6
		{ XMVectorSet( 1,  1,  1, 1), XMVectorSet(0.25f, 0.5f, 0, 0), XMVectorSet(0, 0, 1.0, 0) }, // 左上
		{ XMVectorSet(-1,  1, 1, 1),  XMVectorSet(0.50f, 0.5f, 0, 0), XMVectorSet(0, 0, 1.0, 0)}, // 右上
		{ XMVectorSet(-1, -1, 1, 1),  XMVectorSet(0.50f, 1.0f, 0, 0), XMVectorSet(0, 0, 1.0, 0) }, // 右下
		{ XMVectorSet( 1, -1,  1, 1), XMVectorSet(0.25f, 1.0f, 0, 0), XMVectorSet(0, 0, 1.0, 0) }, // 左下
		// 左面5
		{ XMVectorSet(-1,  1,  1, 1), XMVectorSet(0.00f, 0.5f, 0, 0), XMVectorSet(-1.0, 0, 0, 0) }, // 左上
		{ XMVectorSet(-1,  1, -1, 1), XMVectorSet(0.25f, 0.5f, 0, 0), XMVectorSet(-1.0, 0, 0, 0) }, // 右上
		{ XMVectorSet(-1, -1, -1, 1), XMVectorSet(0.25f, 1.0f, 0, 0), XMVectorSet(-1.0, 0, 0, 0) }, // 右下
		{ XMVectorSet(-1, -1,  1, 1), XMVectorSet(0.00f, 1.0f, 0, 0), XMVectorSet(-1.0, 0, 0, 0) }, // 左下
		// 上面3
		{ XMVectorSet(-1,  1,  1, 1), XMVectorSet(0.50f, 0.0f, 0, 0), XMVectorSet(0, 1.0, 0, 0) }, // 左上
		{ XMVectorSet(1,  1,  1, 1),  XMVectorSet(0.75f, 0.0f, 0, 0), XMVectorSet(0, 1.0, 0, 0) }, // 右上
		{ XMVectorSet(1,  1, -1, 1),  XMVectorSet(0.75f, 0.5f, 0, 0), XMVectorSet(0, 1.0, 0, 0) }, // 右下
		{ XMVectorSet(-1,  1, -1, 1), XMVectorSet(0.50f, 0.5f, 0, 0), XMVectorSet(0, 1.0, 0, 0) }, // 左下
		// 底面4
		{ XMVectorSet(-1, -1, -1, 1), XMVectorSet(0.75f, 0.0f, 0, 0), XMVectorSet(0, -1.0, 0, 0) }, // 左上
		{ XMVectorSet(1, -1, -1, 1),  XMVectorSet(1.00f, 0.0f, 0, 0), XMVectorSet(0, -1.0, 0, 0) }, // 右上
		{ XMVectorSet(1, -1,  1, 1),  XMVectorSet(1.00f, 0.5f, 0, 0), XMVectorSet(0, -1.0, 0, 0) }, // 右下
		{ XMVectorSet(-1, -1,  1, 1), XMVectorSet(0.75f, 0.5f, 0, 0), XMVectorSet(0, -1.0, 0, 0) }, // 左下
	};

	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"頂点バッファの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}

	//インデックス情報
	int index[] = {
		// 前面
		0,1,2, 0,2,3,
		// 右面
		4,5,6, 4,6,7,
		// 背面
		8,9,10, 8,10,11,
		// 左面
		12,13,14, 12,14,15,
		// 上面
		16,17,18, 16,18,19,
		// 底面
		20,21,22, 20,22,23
	};

	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"インデックスバッファの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}

	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"コンスタントバッファの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}
	pTexture_ = new Texture;
	pTexture_->Load("dice.png");
	return S_OK;

}

void Quad::Draw(XMMATRIX& worldMatrix)
{
	// コンスタントバッファに渡す情報

	//XMVECTOR position = { 0, 3, -10, 0 };	//カメラの位置
	//XMVECTOR target = { 0, 0, 0, 0 };	//カメラの焦点
	//XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0));	//ビュー行列
	//XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600.0f, 0.1f, 100.0f);//射影行列

	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	cb.matW = XMMatrixTranspose(worldMatrix);

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//再開
	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	Direct3D::pContext->DrawIndexed(36, 0, 0);
}

void Quad::Release()
{
	if (pTexture_) 
	{
		pTexture_->Release(); // リソース解放（delete this;しない前提）
		delete pTexture_;     // メモリ解放
		pTexture_ = nullptr;
	}

	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);	
}