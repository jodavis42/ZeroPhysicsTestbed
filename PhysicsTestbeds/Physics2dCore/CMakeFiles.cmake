################################################################################
# Generated using Joshua T. Fisher's 'CMake Builder'.
# Link: https://github.com/playmer/CmakeBuilder 
################################################################################
target_sources(Physics2dCore
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Physics2dCoreStandard.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Physics2dCoreStandard.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Integrators2d.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Integrators2d.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SimpleIntersection.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SimpleIntersection.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Shapes/Aabb2d.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Shapes/Aabb2d.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Shapes/Box2d.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Shapes/Box2d.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Shapes/Circle2d.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Shapes/Circle2d.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Manifold2d.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Constraints/Jacobian2d.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Constraints/ConstraintVelocities2d.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Constraints/ConstraintMass2d.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Constraints/Constraint2dMath.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Constraints/Constraint2dMath.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Constraints/Constraint2dMolecule.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Constraints/Constraint2dVector.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Constraints/Constraint2dVector.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SpatialPartitions/NSquaredSpatialPartition.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SpatialPartitions/SpatialPartitionData.hpp
)
