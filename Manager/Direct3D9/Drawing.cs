using System;
using System.Drawing;
using System.Runtime.InteropServices;

using SharpDX;
using SharpDX.Direct3D9;
using SharpDX.Mathematics.Interop;

using IVSDKDotNet.Direct3D9;

using Vector2 =     System.Numerics.Vector2;
using Vector3 =     System.Numerics.Vector3;
using Color =       System.Drawing.Color;
using Point =       System.Drawing.Point;
using RectangleF =  System.Drawing.RectangleF;

namespace Manager.Direct3D9 {
    internal class Drawing {

        public struct Vertex {

            #region Variables
            public float x, y, z, rhw;
            public int color;
            #endregion

            #region Constructor
            public Vertex(Vector3 pPos, float pRhw, Color pColor)
            {
                x = pPos.X;
                y = pPos.Y;
                z = pPos.Z;
                rhw = pRhw;
                color = pColor.ToArgb();
            }
            #endregion

        };

        public static bool DrawLines(D3DGraphics g, IntPtr device, RawVector2[] vertices, Color color, bool antialias, int pattern, float patternScale, float thickness)
        {
            try {
                using (Line l = new Line((Device)device)) {
                    l.Antialias = antialias;
                    l.Pattern = pattern;
                    l.PatternScale = patternScale;
                    l.Width = thickness;
                    l.Draw(vertices, color.ToRawColorBGRA());
                }
                return true;
            }
            catch (Exception ex) {
                Main.managerInstance.console.PrintError(string.Format("[Direct3D9] An error occured while trying to draw line. Details: {0}", ex.ToString()));
            }
            return false;
        }
        public static bool DrawLine(D3DGraphics g, IntPtr device, Vector2 point1, Vector2 point2, Color color, bool antialias, int pattern, float patternScale, float thickness)
        {
            RawVector2[] vertices = new RawVector2[2] {
                point1.ToRawVector2(),
                point2.ToRawVector2()
            };

            return DrawLines(g, device, vertices, color, antialias, pattern, patternScale, thickness);
        }

        public static bool DrawCircle(D3DGraphics g, IntPtr device, Vector2 pos, float radius, float rotation, eD3DCircleType type, bool smoothing, int resolution, Color color)
        {
            try {
                Vertex[] vertex = new Vertex[resolution + 2];

                // Circle Type
                float pi = 0f;
                if (type == eD3DCircleType.Full)    pi = (float)Math.PI;         // Full circle
                if (type == eD3DCircleType.Half)    pi = (float)Math.PI / 2f;    // 1/2 circle
                if (type == eD3DCircleType.Quarter) pi = (float)Math.PI / 4f;    // 1/4 circle

                for (int i = 0; i < vertex.Length; i++) {
                    vertex[i].x = (float)(pos.X - radius * Math.Cos(i * (2 * pi / resolution)));
                    vertex[i].y = (float)(pos.Y - radius * Math.Sin(i * (2 * pi / resolution)));
                    vertex[i].z = 0f;
                    vertex[i].rhw = 1f;
                    vertex[i].color = color.ToArgb();
                }

                // Rotate matrix
                float angle = rotation * (float)Math.PI / 180f;
                for (int i = 0; i < vertex.Length; i++) {

                    // Translate point back to origin
                    vertex[i].x -= pos.X;
                    vertex[i].y -= pos.Y;

                    // Rotate point
                    float xNew = (float)(vertex[i].x * Math.Cos(angle) - vertex[i].y * Math.Sin(angle));
                    float yNew = (float)(vertex[i].x * Math.Sin(angle) + vertex[i].y * Math.Cos(angle));

                    // Translate point back
                    vertex[i].x = xNew + pos.X;
                    vertex[i].y = yNew + pos.Y;

                }

                // Cast IntPtr to Direct3D9.Device
                Device d = (Device)device;

                // Create VertexBuffer, copy vertex array into VertexBuffer
                VertexBuffer g_pVB = new VertexBuffer(d, vertex.Length * Marshal.SizeOf(typeof(Vertex)), Usage.WriteOnly, VertexFormat.PositionRhw | VertexFormat.Diffuse, Pool.Managed);
                DataStream ds = g_pVB.Lock(0, vertex.Length * Marshal.SizeOf(typeof(Vertex)), LockFlags.None);
                ds.WriteRange(vertex);
                g_pVB.Unlock();

                if (smoothing) {
                    d.SetRenderState(RenderState.MultisampleAntialias, true);
                    d.SetRenderState(RenderState.AntialiasedLineEnable, true);
                }

                // Set sources and VertexFormat
                d.SetStreamSource(0, g_pVB, 0, Marshal.SizeOf(typeof(Vertex)));
                d.VertexFormat = VertexFormat.PositionRhw | VertexFormat.Diffuse;

                // Draw
                d.DrawPrimitives(PrimitiveType.LineStrip, 0, resolution);

                // Cleanup
                if (g_pVB != null) g_pVB.Dispose();

                return true;
            }
            catch (Exception ex) {
                Main.managerInstance.console.PrintError(string.Format("[Direct3D9] An error occured while trying to draw circle. Details: {0}", ex.ToString()));
            }
            return false;
        }
        public static bool DrawCircleFilled(D3DGraphics g, IntPtr device, Vector2 pos, float radius, float rotation, eD3DCircleType type, bool smoothing, int resolution, Color color)
        {
            try {
                Vertex[] vertex = new Vertex[resolution + 2];

                // Circle Type
                float pi = 0f;
                if (type == eD3DCircleType.Full)    pi = (float)Math.PI;         // Full circle
                if (type == eD3DCircleType.Half)    pi = (float)Math.PI / 2f;    // 1/2 circle
                if (type == eD3DCircleType.Quarter) pi = (float)Math.PI / 4f;    // 1/4 circle

                vertex[0].x = pos.X;
                vertex[0].y = pos.Y;
                vertex[0].z = 0f;
                vertex[0].rhw = 1f;
                vertex[0].color = color.ToArgb();

                for (int i = 1; i < vertex.Length; i++) {
                    vertex[i].x = (float)(pos.X - radius * Math.Cos(pi * ((i - 1) / (resolution / 2.0f))));
                    vertex[i].y = (float)(pos.Y - radius * Math.Sin(pi * ((i - 1) / (resolution / 2.0f))));
                    vertex[i].z = 0f;
                    vertex[i].rhw = 1f;
                    vertex[i].color = color.ToArgb();
                }

                // Rotate matrix
                float angle = rotation * (float)Math.PI / 180f;
                for (int i = 0; i < vertex.Length; i++) {

                    // Translate point back to origin
                    vertex[i].x -= pos.X;
                    vertex[i].y -= pos.Y;

                    // Rotate point
                    float xNew = (float)(vertex[i].x * Math.Cos(angle) - vertex[i].y * Math.Sin(angle));
                    float yNew = (float)(vertex[i].x * Math.Sin(angle) + vertex[i].y * Math.Cos(angle));

                    // Translate point back
                    vertex[i].x = xNew + pos.X;
                    vertex[i].y = yNew + pos.Y;

                }

                // Cast IntPtr to Direct3D9.Device
                Device d = (Device)device;

                // Create VertexBuffer, copy vertex array into VertexBuffer
                VertexBuffer g_pVB = new VertexBuffer(d, vertex.Length * Marshal.SizeOf(typeof(Vertex)), Usage.WriteOnly, VertexFormat.PositionRhw | VertexFormat.Diffuse, Pool.Managed);
                DataStream ds = g_pVB.Lock(0, vertex.Length * Marshal.SizeOf(typeof(Vertex)), LockFlags.None);
                ds.WriteRange(vertex);
                g_pVB.Unlock();

                if (smoothing) {
                    d.SetRenderState(RenderState.MultisampleAntialias, true);
                    d.SetRenderState(RenderState.AntialiasedLineEnable, true);
                }

                // Set sources and VertexFormat
                d.SetStreamSource(0, g_pVB, 0, Marshal.SizeOf(typeof(Vertex)));
                d.VertexFormat = VertexFormat.PositionRhw | VertexFormat.Diffuse;

                // Draw
                d.DrawPrimitives(PrimitiveType.TriangleFan, 0, resolution);

                // Cleanup
                if (g_pVB != null) g_pVB.Dispose();

                return true;
            }
            catch (Exception ex) {
                Main.managerInstance.console.PrintError(string.Format("[Direct3D9] An error occured while trying to draw filled circle. Details: {0}", ex.ToString()));
            }
            return false;
        }

        public static bool DrawBoxFilled(D3DGraphics g, IntPtr device, Vector2 pos, SizeF size, Color color)
        {
            try {
                Vertex[] vertex = new Vertex[4];

                for (int i = 0; i < vertex.Length; i++) {
                    vertex[i].z = 0f;
                    vertex[i].rhw = 0f;
                    vertex[i].color = color.ToArgb();
                }

                // Set vertex positions
                vertex[0].x = pos.X;
                vertex[0].y = pos.Y;
                vertex[1].x = pos.X + size.Width;
                vertex[1].y = pos.Y;
                vertex[2].x = pos.X + size.Width;
                vertex[2].y = pos.Y + size.Height;
                vertex[3].x = pos.X;
                vertex[3].y = pos.Y + size.Height;

                short[] indexes = new short[] { 0, 1, 3, 1, 2, 3 };

                // Cast IntPtr to Direct3D9.Device
                Device d = (Device)device;

                // Create VertexBuffer, copy vertex array into VertexBuffer
                VertexBuffer g_pVB = new VertexBuffer(d, vertex.Length * Marshal.SizeOf(typeof(Vertex)), Usage.WriteOnly, VertexFormat.PositionRhw | VertexFormat.Diffuse, Pool.Managed);
                DataStream ds = g_pVB.Lock(0, vertex.Length * Marshal.SizeOf(typeof(Vertex)), LockFlags.None);
                ds.WriteRange(vertex);
                g_pVB.Unlock();

                // Create IndexBuffer, copy indexes array into IndexBuffer
                IndexBuffer g_pIB = new IndexBuffer(d, indexes.Length * Marshal.SizeOf(typeof(short)), Usage.WriteOnly, Pool.Managed, true);
                DataStream ds2 = g_pIB.Lock(0, indexes.Length * Marshal.SizeOf(typeof(short)), LockFlags.None);
                ds2.WriteRange(indexes);
                g_pIB.Unlock();

                // Set sources and VertexFormat
                d.SetStreamSource(0, g_pVB, 0, Marshal.SizeOf(typeof(Vertex)));
                d.VertexFormat = VertexFormat.PositionRhw | VertexFormat.Diffuse;
                d.Indices = g_pIB;

                // Draw
                d.DrawIndexedPrimitive(PrimitiveType.TriangleList, 0, 0, 4, 0, 2);

                // Cleanup
                if (g_pVB != null) g_pVB.Dispose();
                if (g_pIB != null) g_pIB.Dispose();

                return true;
            }
            catch (Exception ex) {
                Main.managerInstance.console.PrintError(string.Format("[Direct3D9] An error occured while trying to draw filled box. Details: {0}", ex.ToString()));
            }
            return false;
        }
        public static bool DrawBox(D3DGraphics g, IntPtr device, Vector2 pos, SizeF size, float lineWidth, Color color)
        {
            if (lineWidth == 0 || lineWidth == 1) {
                DrawBoxFilled(g, device, pos, new SizeF(size.Width, 1f), color);                                                           // Top
                DrawBoxFilled(g, device, new Vector2(pos.X, pos.Y + size.Height - 1), new SizeF(size.Width, 1f), color);                   // Bottom
                DrawBoxFilled(g, device, new Vector2(pos.X, pos.Y + 1f), new SizeF(1f, size.Height - 2f * 1f), color);                     // Left
                DrawBoxFilled(g, device, new Vector2(pos.X + size.Width - 1f, pos.Y + 1f), new SizeF(1f, size.Height - 2f * 1f), color);   // Right
            }
            else {
                DrawBoxFilled(g, device, pos, new SizeF(size.Width, lineWidth), color);                                                                                // Top
                DrawBoxFilled(g, device, new Vector2(pos.X, pos.Y + size.Height - lineWidth), new SizeF(size.Width, lineWidth), color);                                // Bottom
                DrawBoxFilled(g, device, new Vector2(pos.X, pos.Y + lineWidth), new SizeF(lineWidth, size.Height - 2f * lineWidth), color);                            // Left
                DrawBoxFilled(g, device, new Vector2(pos.X + size.Width - lineWidth, pos.Y + lineWidth), new SizeF(lineWidth, size.Height - 2f * lineWidth), color);   // Right
            }
            return true;
        }
        public static bool DrawBoxBordered(D3DGraphics g, IntPtr device, Vector2 pos, SizeF size, float borderWidth, Color color, Color borderColor)
        {
            DrawBoxFilled(g, device, pos, size, color);
            DrawBox(g, device, new Vector2(pos.X - borderWidth, pos.Y - borderWidth), new SizeF(size.Width + 2 * borderWidth, size.Height + borderWidth), borderWidth, borderColor);
            return true;
        }
        public static bool DrawBoxRounded(D3DGraphics g, IntPtr device, Vector2 pos, SizeF size, float radius, bool smoothing, Color color, Color borderColor)
        {
            DrawBoxFilled(g, device, new Vector2(pos.X + radius, pos.Y + radius), new SizeF(size.Width - 2f * radius - 1f, size.Height - 2f * radius - 1f), color);    // Center rect.
            DrawBoxFilled(g, device, new Vector2(pos.X + radius, pos.Y + 1f), new SizeF(size.Width - 2f * radius - 1f, radius - 1f), color);                           // Top rect.
            DrawBoxFilled(g, device, new Vector2(pos.X + radius, pos.Y + size.Height - radius - 1f), new SizeF(size.Width - 2f * radius - 1f, radius), color);         // Bottom rect.
            DrawBoxFilled(g, device, new Vector2(pos.X + 1f, pos.Y + radius), new SizeF(radius - 1f, size.Height - 2f * radius - 1f), color);                          // Left rect.
            DrawBoxFilled(g, device, new Vector2(pos.X + size.Width - radius - 1f, pos.Y + radius), new SizeF(radius, size.Height - 2f * radius - 1f), color);         // Right rect.

            // Smoothing method
            if (smoothing) {
                DrawCircleFilled(g, device, new Vector2(pos.X + radius, pos.Y + radius), radius - 1f, 0f, eD3DCircleType.Quarter, false, 16, color);                                               // Top-left corner
                DrawCircleFilled(g, device, new Vector2(pos.X + size.Width - radius - 1f, pos.Y + radius), radius - 1f, 90f, eD3DCircleType.Quarter, false, 16, color);                            // Top-right corner
                DrawCircleFilled(g, device, new Vector2(pos.X + size.Width - radius - 1f, pos.Y + size.Height - radius - 1f), radius - 1f, 180f, eD3DCircleType.Quarter, false, 16, color);        // Bottom-right corner
                DrawCircleFilled(g, device, new Vector2(pos.X + radius, pos.Y + size.Height - radius - 1f), radius - 1f, 270f, eD3DCircleType.Quarter, false, 16, color);                          // Bottom-left corner

                DrawCircle(g, device, new Vector2(pos.X + radius + 1f, pos.Y + radius + 1f), radius, 0f, eD3DCircleType.Quarter, true, 16, borderColor);                                    // Top-left corner
                DrawCircle(g, device, new Vector2(pos.X + size.Width - radius - 2f, pos.Y + radius + 1f), radius, 90f, eD3DCircleType.Quarter, true, 16, borderColor);                      // Top-right corner
                DrawCircle(g, device, new Vector2(pos.X + size.Width - radius - 2f, pos.Y + size.Height - radius - 2f), radius, 180f, eD3DCircleType.Quarter, true, 16, borderColor);       // Bottom-right corner
                DrawCircle(g, device, new Vector2(pos.X + radius + 1f, pos.Y + size.Height - radius - 2f), radius, 270f, eD3DCircleType.Quarter, true, 16, borderColor);                    // Bottom-left corner

                DrawLine(g, device, new Vector2(pos.X + radius, pos.Y + 1f), new Vector2(pos.X + size.Width - radius - 1f, pos.Y + 1f), borderColor, false, -1, 1.0f, 1f);                                 // Top line
                DrawLine(g, device, new Vector2(pos.X + radius, pos.Y + size.Height - 2f), new Vector2(pos.X + size.Width - radius - 1f, pos.Y + size.Height - 2f), borderColor, false, -1, 1.0f, 1f);     // Bottom line
                DrawLine(g, device, new Vector2(pos.X + 1f, pos.Y + radius), new Vector2(pos.X + 1f, pos.Y + size.Height - radius - 1f), borderColor, false, -1, 1.0f, 1f);                                // Left line
                DrawLine(g, device, new Vector2(pos.X + size.Width - 2f, pos.Y + radius), new Vector2(pos.X + size.Width - 2f, pos.Y + size.Height - radius - 1f), borderColor, false, -1, 1.0f, 1f);      // Right line
            }
            else {
                DrawCircleFilled(g, device, new Vector2(pos.X + radius, pos.Y + radius), radius, 0f, eD3DCircleType.Quarter, false, 16, color);                                                    // Top-left corner
                DrawCircleFilled(g, device, new Vector2(pos.X + size.Width - radius - 1f, pos.Y + radius), radius, 90f, eD3DCircleType.Quarter, false, 16, color);                                 // Top-right corner
                DrawCircleFilled(g, device, new Vector2(pos.X + size.Width - radius - 1f, pos.Y + size.Height - radius - 1f), radius, 180f, eD3DCircleType.Quarter, false, 16, color);             // Bottom-right corner
                DrawCircleFilled(g, device, new Vector2(pos.X + radius, pos.Y + size.Height - radius - 1f), radius, 270f, eD3DCircleType.Quarter, false, 16, color);                               // Bottom-left corner
            }

            return true;
        }

        public static bool DrawTexture(D3DGraphics g, IntPtr device, IntPtr txt, RectangleF rect, float rotation, Color tint)
        {
            try {
                Texture texture = (Texture)txt;

                // Convert pixel to screen units
                SurfaceDescription sd = texture.GetLevelDescription(0);
                float cW = rect.Width / sd.Width;
                float cH = rect.Height / sd.Height;

                // Create matrix for texture
                Matrix m = Matrix.Transformation2D(SharpDX.Vector2.Zero, 0f, new SharpDX.Vector2(cW, cH), new SharpDX.Vector2(rect.Width / 2, rect.Height / 2), rotation, new SharpDX.Vector2(rect.X, rect.Y));
                //Matrix m = Matrix.Identity * Matrix.Translation(-0.5f, -0.5f, 0.0f) * Matrix.Scaling(cW, cH, 1.0f) * Matrix.RotationZ(rotation) * Matrix.Translation(rect.X, rect.Y, 0.0f);
                
                // Draw texture on screen
                using (Sprite s = new Sprite((Device)device)) {
                    s.Begin();
                    s.Transform = m;
                    s.Draw(texture, tint.ToRawColorBGRA());
                    s.End();
                }

                return true;
            }
            catch (Exception ex) {
                Main.managerInstance.console.PrintError(string.Format("[Direct3D9] An error occured while trying to draw texture. Details: {0}", ex.ToString()));
            }
            return false;
        }

        public static bool DrawString(D3DGraphics g, IntPtr fontPtr, string text, RawRectangle rect, eD3DFontDrawFlags drawFlags, Color color)
        {
            try
            {
                if (string.IsNullOrEmpty(text))
                    return false;

                SharpDX.Direct3D9.Font f = (SharpDX.Direct3D9.Font)fontPtr;
                if (f != null)
                {
                    f.DrawText(null, text, rect, (FontDrawFlags)drawFlags, color.ToRawColorBGRA());
                    return true;
                }
                return false;
            }
            catch (Exception ex)
            {
                Main.managerInstance.console.PrintError(string.Format("[Direct3D9] An error occured while trying to draw text. Details: {0}", ex.ToString()));
            }
            return false;
        }
        public static bool DrawString(D3DGraphics g, IntPtr fontPtr, string text, Point pos, Color color)
        {
            try {
                if (string.IsNullOrEmpty(text))
                    return false;

                SharpDX.Direct3D9.Font f = (SharpDX.Direct3D9.Font)fontPtr;
                if (f != null) {
                    f.DrawText(null, text, pos.X, pos.Y, color.ToRawColorBGRA());
                    return true;
                }
                return false;
            }
            catch (Exception ex) {
                Main.managerInstance.console.PrintError(string.Format("[Direct3D9] An error occured while trying to draw text. Details: {0}", ex.ToString()));
            }
            return false;
        }

    }
}
