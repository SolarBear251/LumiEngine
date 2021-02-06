// #include <cassert>
// #include <iostream>

// #include "LinearAlgebra.hpp"

// using namespace std;
// using namespace Lumi::Math;

// void vector_test() {
//     Vec2f x = {55.3f, 22.1f};
//     cout << "Vec2f: ";
//     cout << x << endl;

//     Vec3f a = {1.0f, 2.0f, 3.0f};
//     Vec3f b = {5.0f, 6.0f, 7.0f};

//     cout << "vec 1: ";
//     cout << a << endl;
//     cout << "vec 2: ";
//     cout << b << endl;

//     Vec3f c;
//     c = a.cross3(b);
//     cout << "Cross Product of vec 1 and vec 2: ";
//     cout << c << endl;

//     float d;
//     d = a.dot(b);
//     cout << "Dot Product of vec 1 and vec 2: ";
//     cout << d << endl;

//     c = a * b;
//     cout << "Element Product of vec 1 and vec 2: ";
//     cout << c << endl;

//     Vec4f e = {-3.0f, 3.0f, 6.0f, 1.0f};
//     Vec4f f = {2.0f, 0.0f, -0.7f, 0.0f};
//     cout << "vec 3: " << e << endl;
//     cout << "vec 4: " << f << endl;

//     Vec4f g = e + f;
//     cout << "vec 3 + vec 4: " << g << endl;
//     g = e - f;
//     cout << "vec 3 - vec 4: " << g << endl;

//     g.normalize();
//     cout << "normalized: " << g << endl;
// }

// void matrix_test() {
//     Mat4x4f m1;
//     m1.setIdentity();

//     cout << "Idendity Matrix: ";
//     cout << m1;

//     Mat4x4f mEu;
//     float yaw = 0.2f, pitch = 0.3f, roll = 0.4f;
//     mEu = buildMat_RotationYawPitchRoll(yaw, pitch, roll);

//     cout << "Matrix of yaw(" << yaw << ") pitch(" << pitch << ") roll(" << roll << "):";
//     cout << mEu;

//     Mat4x4f ry;
//     float angle = PI / 2.0f;
//     ry = buildMat_RotationY(angle);

//     cout << "Matrix of Rotation on Y(angle = " << angle << "):";
//     cout << ry;

//     Mat4x4f rz;
//     rz = buildMat_RotationZ(angle);

//     cout << "Matrix of Rotation on Z(angle = " << angle << "):";
//     cout << rz;

//     float x = 5.0f, y = 6.5f, z = -7.0f;
//     Mat4x4f translate;
//     translate = buildMat_Translation(x, y, z);

//     cout << "Matrix of Translation on X(" << x << ") Y(" << y << ") Z(" << z << "):";
//     cout << translate;

//     cout << "Matrix multiplication: Rotation Y * Rotation Z * Translation on X:";
//     Mat4x4f transform = m1(ry(rz(translate)));
//     cout << transform;

//     Vec3f rotation, scalar, translation;
//     decomposeMat_4x4f(transform, rotation, scalar, translation);
//     cout << "Decompose of Transform Matrix: " << endl;
//     cout << "Rotation: " << rotation << endl;
//     cout << "Scalar: " << scalar << endl;
//     cout << "Translation: " << translation << endl;
//     cout << endl;

//     Mat4x4f recomposed_transform;
//     composeMat_4x4f(recomposed_transform, rotation, scalar, translation);
//     cout << "Re-composed Transform Matrix: " << endl;
//     cout << recomposed_transform;

//     Vec3f v = {1.0f, 0.0f, 0.0f};

//     Vec3f v1 = v;
//     cout << "Vector : " << v1 << endl;
//     cout << "Transform by Rotation Y Matrix:";
//     cout << ry;
//     v1 = ry(v1);
//     cout << "Now the vector becomes: " << v1 << endl;
//     cout << endl;

//     v1 = v;
//     cout << "Vector : " << v1 << endl;
//     cout << "Transform by Rotation Z Matrix:";
//     cout << rz;
//     v1 = rz(v1);
//     cout << "Now the vector becomes: " << v1 << endl;
//     cout << endl;

//     v1 = v;
//     cout << "Vector : " << v1 << endl;
//     cout << "Transform by Translation Matrix:";
//     cout << translate;
//     v1 = translate(v1);
//     cout << "Now the vector becomes: " << v1 << endl;
//     cout << endl;

//     v1 = v;
//     cout << "Vector : " << v1 << endl;
//     cout << "Transform by Transform Matrix:";
//     cout << transform;
//     v1 = transform(v1);
//     cout << "Now the vector becomes: " << v1 << endl;
//     cout << endl;

//     Vec3f v2 = v;
//     cout << "Vector : " << v2 << endl;
//     cout << "Transform by Re-Composed Transform Matrix:";
//     cout << recomposed_transform;
//     v2 = recomposed_transform(v2);
//     cout << "Now the vector becomes: " << v2 << endl;
//     cout << "Error between vector transformed by origin and recomposed "
//             "transform:"
//          << endl;
//     cout << v1 - v2 << endl;
//     cout << endl;
//     assert((v1 - v2).length() < 10E-6f);

//     Vec3f position = {0, 0, -5}, lookAt = {0, 0, 0}, up = {0, 1, 0};
//     Mat4x4f view = buildMat_ViewRightHand(position, lookAt, up);
//     cout << "View Matrix with position(" << position << ") lookAt(" << lookAt << ") up(" << up
//          << "):";
//     cout << view;

//     float fov = PI / 2.0f, aspect = 16.0f / 9.0f, near = 1.0f, far = 100.0f;
//     Mat4x4f perspective = buildMat_PerspectiveFovLeftHand(fov, aspect, near, far);
//     cout << "(Left-Handed Coordinate System) Perspective Matrix with fov(" << fov << ") aspect("
//          << aspect << ") near ... far(" << near << " ... " << far << "):";
//     cout << perspective;

//     perspective = buildMat_PerspectiveFovRightHand(fov, aspect, near, far);
//     cout << "(Right-Handed Coordinate System) Perspective Matrix with fov(" << fov << ") aspect("
//          << aspect << ") near ... far(" << near << " ... " << far << "):";
//     cout << perspective;

//     Mat4x4f mvp = view(perspective);
//     cout << "MVP: " << mvp;

//     Mat3x3f invertable3x3 = {
//         {1.0f, 1.0f, 0.0f},
//         {0.0f, 2.0f, 0.0f},
//         {0.0f, 0.0f, 1.0f},
//     };
//     cout << "Known Invertable Matrix: " << invertable3x3;
//     assert(invertable3x3.inverse());
//     cout << "Inverse of Matrix: " << invertable3x3;

//     Mat4x4f invertable = {
//         {1.0f, 1.0f, 0.0f, 0.0f}, 
//         {0.0f, 2.0f, 0.0f, 0.0f},
//         {0.0f, 0.0f, 1.0f, 0.0f}, 
//         {13.0f, 14.0f, 15.0f, 1.0f}
//     };
//     cout << "Known Invertable Matrix: " << invertable;
//     assert(invertable.inverse());
//     cout << "Inverse of Matrix: " << invertable;

//     Mat4x4f non_invertable = {
//         {1.0f, 2.0f, 3.0f, 4.0f}, 
//         {5.0f, 6.0f, 7.0f, 8.0f},
//         {9.0f, 10.0f, 11.0f, 12.0f}, 
//         {13.0f, 14.0f, 15.0f, 16.0f}
//     };
//     cout << "Known Sigular(Not Invertable) Matrix: " << non_invertable;
//     assert(!non_invertable.inverse());
//     cout << "InverseMat4x4f returns false." << endl;

//     Mat8x8f pixel_block = {
//         {-76, -73, -67, -62, -58, -67, -64, -55}, 
//         {-65, -69, -73, -38, -19, -43, -59, -56},
//         {-66, -69, -60, -15, 16, -24, -62, -55},
//         {-65, -70, -57, -6, 26, -22, -58, -59},
//         {-61, -67, -60, -24, -2, -40, -60, -58}, 
//         {-49, -63, -68, -58, -51, -60, -70, -53},
//         {-43, -57, -64, -69, -73, -67, -63, -45}, 
//         {-41, -49, -59, -60, -63, -52, -50, -34}
//     };
//     cout << "A 8X8 int pixel block: " << pixel_block;
//     Mat8x8f pixel_block_dct = DCT8x8(pixel_block);
//     cout << "After DCTII: " << pixel_block_dct;

//     Mat8x8f pixel_block_reconstructed = IDCT8x8(pixel_block_dct);
//     cout << "After IDCTII: " << pixel_block_reconstructed;

//     Mat8x8f pixel_error = pixel_block_reconstructed - pixel_block;
//     cout << "DCT-IDCT error: " << pixel_error;
// }

// int main() {
//     cout << fixed;

//     vector_test();
//     matrix_test();

//     return 0;
// }