//-----------------------------------------------------------------------------
// Copyright (c) 2015 Andrew Mac
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------


#ifndef HDR_COMPONENT_H
#define HDR_COMPONENT_H

#ifndef _CONSOLEINTERNAL_H_
#include "console/consoleInternal.h"
#endif

#ifndef _RENDERING_H_
#include "rendering/rendering.h"
#endif

#ifndef BGFX_H_HEADER_GUARD
#include <bgfx/bgfx.h>
#endif

#ifndef _RENDER_CAMERA_H
#include "rendering/renderCamera.h"
#endif

#ifndef _BASE_COMPONENT_H_
#include <scene/components/baseComponent.h>
#endif

namespace Scene
{
   // HDR: High Dynamic Range
   // Based On: https://github.com/bkaradzic/bgfx/tree/master/examples/09-hdr

   class HDRComponent : public Scene::BaseComponent, public Rendering::RenderPostProcess
   {
      private:
         typedef Scene::BaseComponent Parent;

      protected:
         F32 mTexelHalf;
         F32 mMiddleGray;
         F32 mWhite;
         F32 mThreshold;
         bool mAutoExposure;
         F32 mExposure;

         Graphics::ViewTableEntry* mLuminanceView;
         Graphics::ViewTableEntry* mDownscale_Luminance0View;
         Graphics::ViewTableEntry* mDownscale_Luminance1View;
         Graphics::ViewTableEntry* mDownscale_Luminance2View;
         Graphics::ViewTableEntry* mDownscale_Luminance3View;
         Graphics::ViewTableEntry* mBrightnessView;
         Graphics::ViewTableEntry* mBlurYView;
         Graphics::ViewTableEntry* mBlurX_TonemapView;

         bgfx::UniformHandle mTonemapUniform;
         bgfx::UniformHandle mOffsetUniform;

         bgfx::FrameBufferHandle mLuminanceBuffer[5];
         bgfx::FrameBufferHandle mBrightBuffer;
         bgfx::FrameBufferHandle mBlurBuffer;

         Graphics::Shader* mLumShader;
         Graphics::Shader* mLumAvgShader;
         Graphics::Shader* mBlurShader;
         Graphics::Shader* mBrightShader;
         Graphics::Shader* mTonemapShader;
         Graphics::Shader* mTonemapAutoShader;

         void setOffsets2x2Lum(bgfx::UniformHandle _handle, U32 _width, U32 _height);
         void setOffsets4x4Lum(bgfx::UniformHandle _handle, U32 _width, U32 _height);

      public:
         HDRComponent();
         ~HDRComponent();

         virtual void onAddToScene();
         virtual void onRemoveFromScene();

         virtual void onAddToCamera();
         virtual void onRemoveFromCamera();

         virtual void process();

         static void initPersistFields();

         F32 getMiddleGray() const { return mMiddleGray; }
         void setMiddleGray(F32 val) { mMiddleGray = val; }
         F32 getWhitePoint() const { return mWhite; }
         void setWhitePoint(F32 val) { mWhite = val; }
         F32 getThreshold() const { return mThreshold; }
         void setThreshold(F32 val) { mThreshold = val; }
         bool getAutoExposure() const { return mAutoExposure; }
         void setAutoExposure(bool val) { mAutoExposure = val; }
         F32 getExposure() const { return mExposure; }
         void setExposure(F32 val) { mExposure = val; }

         DECLARE_CONOBJECT(HDRComponent);
   };
}

#endif