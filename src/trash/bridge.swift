import Foundation

@_cdecl("delete_file_or_directory")
public func delete_file_or_directory(
    path: UnsafePointer<CChar>,
    err: UnsafeMutablePointer<UnsafeMutablePointer<CChar>?>
) {
    let filePath = String(cString: path)
    let url = URL(fileURLWithPath: filePath)

    do {
        try FileManager.default.trashItem(at: url, resultingItemURL: nil)
        err.pointee = nil
    } catch {
        err.pointee = strdup(error.localizedDescription)
    }
}
