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
            // 게임 시작을 백그라운드 쓰레드로 실행
            Task.Run(() =>
            {
                game.StartGame(); // native C++ 게임 루프
            });
        }

        private void EndGame_Click(object sender, RoutedEventArgs e)
        {
            game.EndGame();    // C++ EndGame() 호출
        }

        public static void ShowImages(List<List<string>> paths)
        {

            // 스레드 충돌 나서 추가한 부분
            Application.Current.Dispatcher.Invoke(() =>
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
                        }
                        else
                        {
                            if (!File.Exists(path))
                            {
                                Debug.WriteLine($"[ERROR] 파일이 존재하지 않습니다: {path}");
                                continue;
                            }

                            var image = new Image
                            {
                                Source = new BitmapImage(new Uri(System.IO.Path.GetFullPath(path), UriKind.Absolute)),
                                Stretch = Stretch.Uniform
                            };
                            Grid.SetRow(image, r);
                            Grid.SetColumn(image, c);
                            window.ImageGrid.Children.Add(image);
                        }
                    }
                }
            });
        }
    }
}