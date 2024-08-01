#ifndef PROTOREFLECTIONDESCRIPTORDATABASE_H
#define PROTOREFLECTIONDESCRIPTORDATABASE_H

#include "proto/reflection.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <google/protobuf/descriptor_database.h>

namespace grpc {
    class ProtoReflectionDescriptorDatabase : public google::protobuf::DescriptorDatabase{
public:
    explicit ProtoReflectionDescriptorDatabase(
        std::unique_ptr<reflection::ServerReflection::Stub> stub);
    explicit ProtoReflectionDescriptorDatabase(
        const std::shared_ptr<ChannelInterface>& channel);

    ~ProtoReflectionDescriptorDatabase() override;

    // The following four methods implement DescriptorDatabase interfaces.
    //
    // Find a file by file name.  Fills in *output and returns true if found.
    // Otherwise, returns false, leaving the contents of *output undefined.
    bool FindFileByName(const std::string& filename,
        google::protobuf::FileDescriptorProto* output) override;

    // Find the file that declares the given fully-qualified symbol name.
    // If found, fills in *output and returns true, otherwise returns false
    // and leaves *output undefined.
    bool FindFileContainingSymbol(const std::string& symbol_name,
        google::protobuf::FileDescriptorProto* output) override;

    // Find the file which defines an extension extending the given message type
    // with the given field number.  If found, fills in *output and returns true,
    // otherwise returns false and leaves *output undefined.  containing_type
    // must be a fully-qualified type name.
    bool FindFileContainingExtension(
        const std::string& containing_type, int field_number,
        google::protobuf::FileDescriptorProto* output) override;

    // Finds the tag numbers used by all known extensions of
    // extendee_type, and appends them to output in an undefined
    // order. This method is best-effort: it's not guaranteed that the
    // database will find all extensions, and it's not guaranteed that
    // FindFileContainingExtension will return true on all of the found
    // numbers. Returns true if the search was successful, otherwise
    // returns false and leaves output unchanged.
    bool FindAllExtensionNumbers(const std::string& extendee_type,
        std::vector<int>* output) override;

    // Provide a list of full names of registered services
    bool GetServices(std::vector<std::string>* output);

private:
    typedef ClientReaderWriter<
        reflection::ServerReflectionRequest,
        reflection::ServerReflectionResponse>
        ClientStream;

    google::protobuf::FileDescriptorProto ParseFileDescriptorProtoResponse(const std::string& byte_fd_proto);

    void AddFileFromResponse(const reflection::FileDescriptorResponse& response);

    std::shared_ptr<ClientStream> GetStream();

    bool DoOneRequest(const reflection::ServerReflectionRequest& request,
        reflection::ServerReflectionResponse& response);

    std::shared_ptr<ClientStream> stream_;
    ClientContext ctx_;
    std::unique_ptr<reflection::ServerReflection::Stub> stub_;
    std::unordered_set<std::string> known_files_;
    std::unordered_set<std::string> missing_symbols_;
    std::unordered_map<std::string, std::unordered_set<int>> missing_extensions_;
    std::unordered_map<std::string, std::vector<int>> cached_extension_numbers_;
    std::mutex stream_mutex_;

    google::protobuf::SimpleDescriptorDatabase cached_db_;
};
}

#endif //PROTOREFLECTIONDESCRIPTORDATABASE_H