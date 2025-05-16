#include "Interop.h"
#include "OCCTViewer.h"

struct ViewerWrapper {
    OCCTViewer impl;
};

extern "C" {

    API VIEWER_HANDLE CreateViewer(void* hwnd, int w, int h) {
        auto* wrapper = new ViewerWrapper;
        if (!wrapper->impl.initialize(hwnd, w, h)) {
            delete wrapper;
            return nullptr;
        }
        return wrapper;
    }

    API void DestroyViewer(VIEWER_HANDLE h) {
        delete static_cast<ViewerWrapper*>(h);
    }

    API bool LoadStepFile(VIEWER_HANDLE h, const wchar_t* path) {
        return static_cast<ViewerWrapper*>(h)->impl.loadStep(path);
    }

    API void ExtractProfiles(VIEWER_HANDLE h) {
        // placeholder: re-show axes
        static_cast<ViewerWrapper*>(h)->impl.displayAxes();
    }

    API void RefreshView(VIEWER_HANDLE h) {
        static_cast<ViewerWrapper*>(h)->impl.refresh();
    }

    API void ResizeView(VIEWER_HANDLE h, int w, int hh) {
        static_cast<ViewerWrapper*>(h)->impl.resize(w, hh);
    }

} // extern "C"
