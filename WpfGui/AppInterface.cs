// AppInterface.cs
using System;
using System.Collections.Generic;

// C++/CLI 쪽에 전달할 C# delegate 형식 정의
public delegate void ShowImagesCallback(List<List<string>> paths);