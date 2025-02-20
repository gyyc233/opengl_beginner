- [OPenGL](#opengl)
  - [Graphics Pipeline](#graphics-pipeline)
  - [vertex shader 顶点着色器](#vertex-shader-顶点着色器)
  - [shape assembly 图元装配](#shape-assembly-图元装配)
  - [eometry Shader 几何着色器](#eometry-shader-几何着色器)
  - [Rasterization 光栅化](#rasterization-光栅化)
  - [fragment share 片段着色器](#fragment-share-片段着色器)
  - [test and blending](#test-and-blending)
- [顶点](#顶点)
  - [把顶点数据储存在显卡的内存中，用VBO这个顶点缓冲对象管理](#把顶点数据储存在显卡的内存中用vbo这个顶点缓冲对象管理)
- [vertex shader 顶点着色器](#vertex-shader-顶点着色器-1)

# OPenGL

- 在OpenGL中，任何事物都在3D空间中，而屏幕和窗口却是2D像素数组，这导致OpenGL的大部分工作都是关于把3D坐标转变为适应你屏幕的2D像素
- 3D坐标转为2D坐标的处理过程是由OpenGL的图形渲染管线（Graphics Pipeline，大多译为管线，实际上指的是一堆原始图形数据途经一个输送管道，期间经过各种变化处理最终出现在屏幕的过程）管理的
- 图形渲染管线可以被划分为两个主要部分：第一部分把你的3D坐标转换为2D坐标，第二部分是把2D坐标转变为实际的有颜色的像素

> 2D坐标和像素也是不同的，2D坐标精确表示一个点在2D空间中的位置，而2D像素是这个点的近似值，2D像素受到你的屏幕/窗口分辨率的限制

## Graphics Pipeline

- 图形渲染管线接受一组3D坐标，然后把它们转变为你屏幕上的有色2D像素输出
- 图形渲染管线具有并行执行的特性,它们在GPU上为每一个（渲染管线）阶段运行各自的小程序，从而在图形渲染管线中快速处理你的数据。这些小程序叫做着色器(Shader)
- 有些着色器允许开发者自己配置，这就允许我们用自己写的着色器来替换默认的
- OpenGL着色器是用OpenGL着色器语言(OpenGL Shading Language, GLSL)写成

![](./img/img1.png )

- vertex data[]: 顶点数组
- Primitive 图元: GL_POINTS、GL_TRIANGLES、GL_LINE_STRIP

## vertex shader 顶点着色器

顶点着色器主要的目的是把3D坐标转为另一种3D坐标，同时顶点着色器允许我们对顶点属性进行一些基本处理


## shape assembly 图元装配

图元装配(Primitive Assembly)阶段将顶点着色器输出的所有顶点作为输入（如果是GL_POINTS，那么就是一个顶点），并所有的点装配成指定图元的形状；本节例子中是一个三角形

## eometry Shader 几何着色器

几何着色器把图元形式的一系列顶点的集合作为输入，它可以通过产生新顶点构造出新的（或是其它的）图元来生成其他形状

## Rasterization 光栅化

会把图元映射为最终屏幕上相应的像素，生成供片段着色器(Fragment Shader)使用的片段(Fragment)在片段着色器运行之前会执行裁切(Clipping)。裁切会丢弃超出你的视图以外的所有像素，用来提升执行效率

> OpenGL中的一个片段是OpenGL渲染一个像素所需的所有数据

## fragment share 片段着色器

片段着色器的主要目的是计算一个像素的最终颜色，这也是所有OpenGL高级效果产生的地方。通常，片段着色器包含3D场景的数据（比如光照、阴影、光的颜色等等），这些数据可以被用来计算最终像素的颜色

## test and blending

在所有对应颜色值确定以后，最终的对象将会被传到最后一个阶段，我们叫做Alpha测试和混合(Blending)阶段

- 这个阶段检测片段的对应的深度（和模板(Stencil)）值（后面会讲），用它们来判断这个像素是其它物体的前面还是后面，决定是否应该丢弃
- 也会检查alpha值（alpha值定义了一个物体的透明度）并对物体进行混合(Blend)
- 所以，即使在片段着色器中计算出来了一个像素输出的颜色，在渲染多个三角形的时候最后的像素颜色也可能完全不同

可以看到，图形渲染管线非常复杂，它包含很多可配置的部分。然而，**对于大多数场合，我们只需要配置顶点和片段着色器就行了**。几何着色器是可选的，通常使用它默认的着色器就行了

在现代OpenGL中，我们必须定义至少一个顶点着色器和一个片段着色器（因为GPU中没有默认的顶点/片段着色器）

# 顶点

## 把顶点数据储存在显卡的内存中，用VBO这个顶点缓冲对象管理

```cpp
GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

GLuint VBO; // ertex Buffer Objects 顶点缓冲对象管理这个vertices内存，它会在GPU内存中储存大量顶点　这个缓冲有一个独一无二的ID
glGenBuffers(1, &VBO); // 使用独立id 生成 VBO object
glBindBuffer(GL_ARRAY_BUFFER, VBO); // 顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 把之前定义的顶点数据复制到缓冲的内存
```

现在我们已经把顶点数据储存在显卡的内存中，用VBO这个顶点缓冲对象管理。下面我们会创建一个顶点和片段着色器来真正处理这些数据

# vertex shader 顶点着色器
