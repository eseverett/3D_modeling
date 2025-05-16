#include "OCCTViewer.h"
#include <Xw_Window.hxx>
#include <Quantity_Color.hxx>

bool OCCTViewer::initialize(void* hwnd, int w, int h) {
    m_driver = new OpenGl_GraphicDriver(GetModuleHandle(nullptr));
    m_viewer = new V3d_Viewer(m_driver);
    m_context = new AIS_InteractiveContext(m_viewer);
    m_view = m_viewer->CreateView();

    Handle(Xw_Window) win = new Xw_Window((Aspect_Handle)hwnd, "OCCTHost");
    m_view->SetWindow(win);
    m_view->SetBackgroundColor(Quantity_NOC_GRAY30);
    m_view->MustBeResized();
    m_view->SetSize(w, h);

    displayAxes();
    m_view->FitAll();
    return true;
}

bool OCCTViewer::loadStep(const wchar_t* path) {
    STEPControl_Reader reader;
    if (reader.ReadFile(std::wstring(path)) != IFSelect_RetDone)
        return false;
    reader.TransferRoots();
    TopoDS_Shape shape = reader.OneShape();
    m_context->Display(new AIS_Shape(shape), Standard_True);
    m_view->FitAll();
    return true;
}

void OCCTViewer::displayAxes() {
    auto axes = new AIS_AxisTriad(m_viewer);
    m_context->Display(axes, Standard_True);
}

void OCCTViewer::refresh() {
    if (m_view) m_view->Redraw();
}

void OCCTViewer::resize(int w, int h) {
    if (m_view) {
        m_view->MustBeResized();
        m_view->SetSize(w, h);
    }
}
