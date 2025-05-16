#pragma once

#include <OpenGl_GraphicDriver.hxx>
#include <V3d_Viewer.hxx>
#include <AIS_InteractiveContext.hxx>
#include <V3d_View.hxx>
#include <AIS_AxisTriad.hxx>
#include <STEPControl_Reader.hxx>

class OCCTViewer {
public:
    // Attach to a native window and set up the 3D view
    bool initialize(void* windowHandle, int width, int height);

    // Load & display a STEP file
    bool loadStep(const wchar_t* filepath);

    // Show the XYZ axes triad for debugging
    void displayAxes();

    // Redraw the scene
    void refresh();

    // Handle host window resize
    void resize(int width, int height);

private:
    Handle(OpenGl_GraphicDriver)    m_driver;
    Handle(V3d_Viewer)              m_viewer;
    Handle(AIS_InteractiveContext)  m_context;
    Handle(V3d_View)                m_view;
};
