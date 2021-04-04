load("@//third_party:codecraft_remotes.bzl", "CC_SWH_OSS_MIRROR")
load("@//bazel/rules:artifactory.bzl", "artifactory_archive")

# TYPE: upstream
# LICENSE: MPL-2
# CONTACT:
def eigen():
    if "eigen" not in native.existing_rules():
        artifactory_archive(
            name = "eigen",
            repo = CC_SWH_OSS_MIRROR,
            path = "eigen-3.3.5.tar.bz2",
            sha256 = "7352bff3ea299e4c7d7fbe31c504f8eb9149d7e685dec5a12fbaa26379f603e2",
            build_file = "//third_party/eigen:eigen.BUILD",
            strip_prefix = "eigen-eigen-b3f3d4950030",
        )
