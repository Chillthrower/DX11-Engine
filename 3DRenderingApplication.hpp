#pragma once

#include "Definitions.hpp"
#include "Application.hpp"

#include <d3d11_2.h>

#include <memory>
#include <DirectXMath.h>
#include "ShaderCollection.hpp"

#include <Cube.hpp>
#include <Sphere.hpp>
#include <Cylinder.hpp>
#include <WindowsXpPipesSimulation.hpp>
#include <Scene.hpp>

struct PerFrameConstantBuffer
{
    DirectX::XMFLOAT4X4 viewProjectionMatrix;
};

struct PerObjectConstantBuffer
{
    DirectX::XMFLOAT4X4 modelMatrix;
    DirectX::XMFLOAT4X4 normalMatrix;
};

struct CameraConstantBuffer
{
    DirectX::XMFLOAT3 cameraPosition;
    float padding;
};

struct MaterialConstantBuffer
{
    DirectX::XMFLOAT4 ambient;
    DirectX::XMFLOAT4 diffuse;
    DirectX::XMFLOAT4 specular;
    float shininess;
    float padding[3];

    MaterialConstantBuffer()
        : ambient(1.0f, 1.0f, 1.0f, 1.0f),
        diffuse(1.0f, 1.0f, 1.0f, 1.0f),
        specular(1.0f, 1.0f, 1.0f, 1.0f),
        shininess(3.0f)
    { }
};

struct LightConstantBuffer
{
    DirectX::XMFLOAT4 Position;
    DirectX::XMFLOAT4 Ambient;
    DirectX::XMFLOAT4 Diffuse;
    DirectX::XMFLOAT4 Specular;
};



class Rendering3DApplication final : public Application
{
public:
    Rendering3DApplication(const std::string& title);
    ~Rendering3DApplication() override;

protected:
    bool Initialize() override;
    bool Load() override;
    void OnResize(
        int32_t width,
        int32_t height) override;
    void Update() override;
    void Render() override;

private:

    void CreateRasterState();
    void CreateDepthStencilView();
    void CreateDepthState();
    void CreateConstantBuffers();
    bool CreateSwapchainResources();
    void DestroySwapchainResources();

    WRL::ComPtr<ID3D11Device> _device = nullptr;
    WRL::ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;
    WRL::ComPtr<IDXGIFactory2> _dxgiFactory = nullptr;
    WRL::ComPtr<IDXGISwapChain1> _swapChain = nullptr;
    WRL::ComPtr<ID3D11RenderTargetView> _renderTarget = nullptr;
    WRL::ComPtr<ID3D11DepthStencilView> _depthTarget = nullptr;
    WRL::ComPtr<ID3D11RasterizerState> _rasterState = nullptr;
    WRL::ComPtr<ID3D11DepthStencilState> _depthState = nullptr;
    WRL::ComPtr<ID3D11Buffer> _cubeVertices = nullptr;
    WRL::ComPtr<ID3D11Buffer> _cubeIndices = nullptr;
    WRL::ComPtr<ID3D11Debug> _debug = nullptr;

    WRL::ComPtr<ID3D11SamplerState> _linearSamplerState = nullptr;
    WRL::ComPtr<ID3D11ShaderResourceView> _textureSrv = nullptr;
    WRL::ComPtr<ID3D11ShaderResourceView> _fallbackTextureSrv = nullptr;

    WRL::ComPtr<ID3D11Buffer> _perFrameConstantBuffer = nullptr;
    WRL::ComPtr<ID3D11Buffer> _cameraConstantBuffer = nullptr;
    WRL::ComPtr<ID3D11Buffer> _lightConstantBuffer = nullptr;
    WRL::ComPtr<ID3D11Buffer> _materialConstantBuffer = nullptr;
    WRL::ComPtr<ID3D11Buffer> _perObjectConstantBuffer = nullptr;

    ShaderCollection _shaderCollection;

    PerFrameConstantBuffer _perFrameConstantBufferData{};
    CameraConstantBuffer _cameraConstantBufferData{};
    LightConstantBuffer _lightConstantBufferData{};
    MaterialConstantBuffer _materialConstantBufferData{};
    PerObjectConstantBuffer _perObjectConstantBufferData{};

    Scene _scene;
};