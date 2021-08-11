**Name:** Uninitialized Transform Exception
**Issue:** https://github.com/ros-perception/ar_track_alvar/pull/79
**Description:** A user discovered that while searching for a transform from the camera frame to a supplied output frame (which is typically the torso, or base link), that when it fails, although it’s handled by a try block, control flow can fall through and the uninitialized (or rather, improperly initialized) transform is used in subsequent computations. It is unclear exactly what value this transform takes on here, when lookupTransform fails, or in general (and it’s quite likely machine-dependent), but it is evidently “usable” for computations and unlikely to be anything close to the expected value. This leads to an incorrectly transformed pose, which then gets published. Presumably, some node will subscribe and the tainted pose, thus tainting any subsequent computations that use the tainted pose.
**Implementation Challenges:** As discussed last Thursday, there are several implementation approaches that could feasibly be used.
We can simply ignore the control flow and show an incorrect transform application. This can be demonstrated within an hour of coding.
We can use Dr. Sullivans approach of allowing values to take on an option type. This would involve implementation in Peirce and lang.
A slightly more involved but possibly more scalable approach is to let a variable take on a set of different states (here, those would be “default” and the expected transform from Cam -> Base Link). This would involve a similar amount of coding to #2, and minimally would be the same. Then, there are two approaches to demonstrate the error that manifests. This is tricky to implement, and a sound implementation will ONLY throw an exception if, amongst a list of states, at least 1 of them can cause a type exception (i.e., if it is not “valid”). This logic will need to get handled by both our semantics and in generating the cmd itself.
**Solution Details:** How we annotate this example depends on the chosen implementation, as described above. In either case, we’d need to define a world space, a standard frame, etc. From there, we would either need to annotate CamToOutput as having a single, an option, or a set interpretation, where the interpretation is or includes a null value. A type error will manifest when we attempt to apply CamToOutput to the tagPoseOutput variable (which subsequently gets published).