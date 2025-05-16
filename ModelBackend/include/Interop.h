#pragma once

#ifdef _WIN32
#define API __declspec(dllexport)
#else
#define API
#endif

// Opaque handle to the viewer instance
typedef void* VIEWER_HANDLE;

extern "C" {
    // Create/destroy
    API VIEWER_HANDLE CreateViewer(void* windowHandle, int width, int height);
    API void           DestroyViewer(VIEWER_HANDLE viewer);

    // Operations
    API bool           LoadStepFile(VIEWER_HANDLE viewer, const wchar_t* path);
    API void           ExtractProfiles(VIEWER_HANDLE viewer);
    API void           RefreshView(VIEWER_HANDLE viewer);
    API void           ResizeView(VIEWER_HANDLE viewer, int width, int height);
}
