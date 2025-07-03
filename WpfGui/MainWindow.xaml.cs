using CppCliWrapper;
using System.Diagnostics;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;

namespace Demon_battle
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Wrapper game;
        public MainWindow()
        {
            InitializeComponent();
            game = new Wrapper();

            //List<List<string>> paths = new List<List<string>>();
            //paths.Add(new List<string> { "../../../../Image/Pairi.png", "../../../../Image/Kkobugi.png" });
            //paths.Add(new List<string> { "../../../../Image/Naong.png", "../../../../Image/Pikachu.png" });
            //ShowImages(paths);

            // Register C# function to be called from C++
            Wrapper.RegisterImageCallback(ShowImages);
        }

        private void StartGame_Click(object sender, RoutedEventArgs e)
        {
            game.StartGame();  // C++ StartGame() 호출
        }

        private void EndGame_Click(object sender, RoutedEventArgs e)
        {
            game.EndGame();    // C++ EndGame() 호출
        }

        public static void ShowImages(List<List<string>> paths)
        {
            var window = (MainWindow)Application.Current.MainWindow;

            window.ImageGrid.Children.Clear();
            window.ImageGrid.RowDefinitions.Clear();
            window.ImageGrid.ColumnDefinitions.Clear();

            window.ControlPanel.Visibility = Visibility.Collapsed;
            window.GamePanel.Visibility = Visibility.Visible;

            int rowCount = paths.Count;
            int colCount = paths[0].Count;

            for (int r = 0; r < rowCount; r++)
                window.ImageGrid.RowDefinitions.Add(new RowDefinition());

            for (int c = 0; c < colCount; c++)
                window.ImageGrid.ColumnDefinitions.Add(new ColumnDefinition());

            for (int r = 0; r < rowCount; r++)
            {
                for (int c = 0; c < colCount; c++)
                {
                    string path = paths[r][c];

                    if (string.IsNullOrWhiteSpace(path))
                    {
                        var rect = new Border
                        {
                            Background = Brushes.White,
                            BorderBrush = Brushes.Gray,
                            BorderThickness = new Thickness(1)
                        };
                        Grid.SetRow(rect, r);
                        Grid.SetColumn(rect, c);
                        window.ImageGrid.Children.Add(rect);
                        continue;
                    }

                    string fullPath = System.IO.Path.GetFullPath(path);
                    if (!File.Exists(fullPath))
                    {
                        Debug.WriteLine($"[ERROR] 이미지 파일 없음: {fullPath}");
                        var errRect = new Border
                        {
                            Background = Brushes.Red,
                            BorderThickness = new Thickness(1)
                        };
                        Grid.SetRow(errRect, r);
                        Grid.SetColumn(errRect, c);
                        window.ImageGrid.Children.Add(errRect);
                    }
                    else
                    {
                        try
                        {
                            var bitmap = new BitmapImage();
                            bitmap.BeginInit();
                            bitmap.UriSource = new Uri(fullPath, UriKind.Absolute);
                            bitmap.CacheOption = BitmapCacheOption.OnLoad; // 즉시 로딩
                            bitmap.EndInit();

                            var image = new Image
                            {
                                Source = bitmap,
                                Stretch = Stretch.Uniform,
                                Width = 64,   // ✔ 크기 지정 (안하면 안 보일 수도 있음)
                                Height = 64
                            };
                            Grid.SetRow(image, r);
                            Grid.SetColumn(image, c);
                            window.GamePanel.Visibility = Visibility.Visible;
                            window.ImageGrid.Children.Add(image);
                        }
                        catch (Exception ex)
                        {
                            Debug.WriteLine($"[ERROR] 이미지 로딩 실패: {fullPath} - {ex.Message}");
                        }
                    }
                }
            }
        }
    }
}