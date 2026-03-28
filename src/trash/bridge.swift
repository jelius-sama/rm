import Foundation

@_cdecl("delete_file_or_directory")
public func delete_file_or_directory(
    path: UnsafePointer<CChar>, error: UnsafeMutablePointer<UnsafeMutablePointer<CChar>?>
) {
    let filePath = String(cString: path)
    let scriptSource = "tell application \"Finder\" to delete POSIX file \"\(filePath)\""

    if let script = NSAppleScript(source: scriptSource) {
        var nsError: NSDictionary?
        script.executeAndReturnError(&nsError)

        if let err = nsError {
            let message = err["NSAppleScriptErrorMessage"] as? String ?? "Unknown AppleScript Error"
            error.pointee = strdup(message)
        }

        error.pointee = nil
    }
}
